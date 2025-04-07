#include <QDebug>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QTextStream>
#include <QVBoxLayout>
#include <QtConcurrent>

#include "dataprocess.h"
#include "resultgraph.h"
#include "thememanager.h"
#include "ui_resultgraphscreen.h"

ResultGraph::ResultGraph(QWidget *parent) : QWidget(parent), ui(new Ui::ResultGraphScreen)
{
    ui->setupUi(this);

    // 主题化阴影设置
    auto &themeMgr = ThemeManager::instance();
    themeMgr.registerWidget(ui->base_navigationbar, "navigation");
    themeMgr.registerWidget(ui->graphWorkplace, "workarea");
    themeMgr.registerWidget(ui->styleBar, "style");

    // 初始化进度条
    prograssBar_V_OP  = new overallValuesPrograssBar(this);
    prograssBar_V_RMS = new overallValuesPrograssBar(this);
    prograssBar_A_OP  = new overallValuesPrograssBar(this);
    prograssBar_A_RMS = new overallValuesPrograssBar(this);

    addOverallValue(prograssBar_V_OP, 15, ui->gridLayout);
    addOverallValue(prograssBar_V_RMS, 60, ui->gridLayout_4);
    addOverallValue(prograssBar_A_OP, 20, ui->gridLayout_5);
    addOverallValue(prograssBar_A_RMS, 30, ui->gridLayout_6);

    // 连接信号槽
    connect(&fftWatcher, &QFutureWatcher<void>::finished, this, [this]() { QApplication::restoreOverrideCursor(); });
    connect(this, &ResultGraph::fftCompleted, this, &ResultGraph::handleFftResults);

    graphInit();
}

ResultGraph::~ResultGraph()
{
    fftWatcher.cancel();
    fftWatcher.waitForFinished();
    delete ui;
}

void ResultGraph::graphInit()
{
    // 加载CSV数据
    QVector<double> baData, deData, feData;
    loadCSVData("F:/code/projects/29_QT_projects/custom_widget/database/12k_144.csv", baData, deData, feData);

    if(baData.isEmpty())
    {
        qDebug() << "BA数据加载失败！";
        return;
    }

    // 时域图初始化
    resultTimeBigraph = new Bigraph(ui->downGraph);
    resultTimeBigraph->frontAxisX->setLabel("t[s]");
    resultTimeBigraph->frontAxisY->setLabel("v[mm/s]");
    resultTimeBigraph->frontGraph->setPen(QPen(Qt::darkBlue));
    resultTimeBigraph->backGraph->setPen(QPen(Qt::darkYellow));

    // 显示部分时域数据（前10000点）
    const int       displayPoints = 10000;
    QVector<double> time(displayPoints);
    const double    Fs = 12000.0;
    for(int i = 0; i < displayPoints; ++i)
    {
        time[i] = i / Fs;
    }
    resultTimeBigraph->addFrontSeriesPoint(time, baData.mid(0, displayPoints));
    resultTimeBigraph->addBackSeriesPoint(time, baData.mid(0, displayPoints));
    resultTimeBigraph->adjustAxisRanges();

    // 频域图初始化
    resultFreqBigraph = new Bigraph(ui->upGraph);
    resultFreqBigraph->frontAxisX->setLabel("f[Hz]");
    resultFreqBigraph->frontAxisY->setLabel("Amplitude[mm/s]");
    resultFreqBigraph->frontGraph->setPen(QPen(Qt::red));
    resultFreqBigraph->backGraph->setPen(QPen(Qt::darkYellow));
    resultFreqBigraph->adjustAxisRanges();

    // 启动异步FFT计算
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QFuture<void> future = QtConcurrent::run([this, deData]() {
        QVector<double> freq, amp;
        computeFFT(deData, freq, amp);
        qDebug() << freq << amp;
        emit fftCompleted(freq, amp);
    });
    fftWatcher.setFuture(future);
}

void ResultGraph::addOverallValue(overallValuesPrograssBar *overallBar, int value, QGridLayout *gridLayout)
{
    overallBar->setRange(0, 100);
    overallBar->setValue(value);
    gridLayout->addWidget(overallBar, 1, 0);  // 添加进度条到布局, 位置在第二行第一列
}

void ResultGraph::loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件：" << filePath;
        return;
    }

    QTextStream in(&file);
    int         lineCount = 0;
    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if(lineCount++ == 0)
            continue;  // 跳过标题行

        QStringList parts = line.split(',');
        if(parts.size() >= 3)
        {
            bool   ok[3];
            double ba = parts[0].toDouble(&ok[0]);
            double de = parts[1].toDouble(&ok[1]);
            double fe = parts[2].toDouble(&ok[2]);

            if(ok[0] && ok[1] && ok[2])
            {
                baData.append(ba);
                deData.append(de);
                feData.append(fe);
            } else
            {
                qDebug() << "行" << lineCount << "数据转换错误";
            }
        } else
        {
            qDebug() << "行" << lineCount << "数据不完整";
        }
    }
    file.close();
}

void ResultGraph::handleFftResults(QVector<double> freq, QVector<double> amp)
{
    resultFreqBigraph->addFrontSeriesPoint(freq, amp);
    resultFreqBigraph->adjustAxisRanges();
    QApplication::restoreOverrideCursor();
}

void ResultGraph::computeFFT(const QVector<double> &baData, QVector<double> &freq, QVector<double> &amp)
{
    const int fftSize = baData.size();
    if(fftSize < 1)
        return;

    // 预处理（去均值 + 汉宁窗）
    const double  mean = std::accumulate(baData.begin(), baData.end(), 0.0) / fftSize;
    double       *in   = fftw_alloc_real(fftSize);
    fftw_complex *out  = fftw_alloc_complex(fftSize / 2 + 1);

    for(int i = 0; i < fftSize; ++i)
    {
        const double window = 0.5 * (1 - cos(2 * M_PI * i / (fftSize - 1)));  // 汉宁窗
        in[i]               = (baData[i] - mean) * window;
    }

    // 执行FFT
    fftw_plan plan = fftw_plan_dft_r2c_1d(fftSize, in, out, FFTW_ESTIMATE);
    fftw_execute(plan);

    // 计算幅值谱
    const double Fs = 12000.0;
    freq.reserve(fftSize / 2 + 1);
    amp.reserve(fftSize / 2 + 1);

    for(int i = 0; i <= fftSize / 2; ++i)
    {
        const double frequency = i * Fs / fftSize;
        freq.append(frequency);

        double magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        magnitude /= fftSize;  // 归一化
        if(i > 0 && i < fftSize / 2)
            magnitude *= 2;  // 单边谱修正
        amp.append(magnitude);
    }

    // 清理资源
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}


overallValuesPrograssBar::overallValuesPrograssBar(QWidget *parent) : QProgressBar(parent)
{
    // 隐藏进度条的文本值
    setTextVisible(false);

    // 设置样式表，清除默认的绿色背景
    setStyleSheet("QProgressBar { background-color: transparent; border: none; }");
}


overallValuesPrograssBar::~overallValuesPrograssBar()
{
}

// 一条竖线在一条横线上滑动, 隐藏进度条的值
void overallValuesPrograssBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);  // 忽略事件参数

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 获取进度条的矩形区域
    QRect rect = this->rect();

    // 计算当前进度对应的竖线位置
    int progressWidth = rect.width() * value() / maximum();

    // 绘制横线
    // 竖线左侧为黑色
    painter.setPen(Qt::black);
    painter.drawLine(rect.left(), rect.height() / 2, progressWidth, rect.height() / 2);

    // 竖线右侧为灰色
    painter.setPen(Qt::gray);
    painter.drawLine(progressWidth, rect.height() / 2, rect.right(), rect.height() / 2);

    // 绘制黑色竖线
    painter.setPen(Qt::black);
    painter.drawLine(progressWidth, rect.top(), progressWidth, rect.bottom());
}
