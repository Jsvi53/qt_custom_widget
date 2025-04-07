#include <QDebug>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QTextStream>
#include <QVBoxLayout>

#include "resultgraph.h"
#include "thememanager.h"
#include "ui_resultgraphscreen.h"

ResultGraph::ResultGraph(QWidget *parent) : QWidget(parent), ui(new Ui::ResultGraphScreen)
{
    ui->setupUi(this);

    // ================ 主题化阴影设置 ================
    auto &themeMgr = ThemeManager::instance();
    themeMgr.registerWidget(ui->base_navigationbar, "navigation");  // 注册需要阴影效果的控件
    themeMgr.registerWidget(ui->graphWorkplace, "workarea");
    themeMgr.registerWidget(ui->styleBar, "style");

    // 整体值
    prograssBar_V_OP  = new overallValuesPrograssBar(this);
    prograssBar_V_RMS = new overallValuesPrograssBar(this);
    prograssBar_A_OP  = new overallValuesPrograssBar(this);
    prograssBar_A_RMS = new overallValuesPrograssBar(this);

    addOverallValue(prograssBar_V_OP, 15, ui->gridLayout);
    addOverallValue(prograssBar_V_RMS, 60, ui->gridLayout_4);
    addOverallValue(prograssBar_A_OP, 20, ui->gridLayout_5);
    addOverallValue(prograssBar_A_RMS, 30, ui->gridLayout_6);
    graphInit();
}

ResultGraph::~ResultGraph()
{
    delete ui;
}

void ResultGraph::graphInit()
{
    // 加载CSV数据
    QVector<double> baData, deData, feData;
    loadCSVData("D:/shawei/temp/qt_custom_widget/database/12k_144.csv", baData, deData, feData);

    if(baData.isEmpty() || deData.isEmpty() || feData.isEmpty())
    {
        qDebug() << "数据加载失败或为空！";
        return;
    }

    // 生成时间轴
    int             N = baData.size();
    QVector<double> time(N);
    const double    Fs = 12000.0;
    for(int i = 0; i < N; ++i) time[i] = i / Fs;

    // 时域图
    resultTimeBigraph = new Bigraph(ui->downGraph);
    resultTimeBigraph->frontAxisX->setLabel("t[s]");
    resultTimeBigraph->frontAxisY->setLabel("v[mm/s]");

    // 配置BA通道绘图，颜色为红色
    resultTimeBigraph->frontGraph->setPen(QPen(Qt::darkBlue));
    resultTimeBigraph->backGraph->setPen(QPen(Qt::darkYellow));
    resultTimeBigraph->addFrontSeriesPoint(time.mid(0, 10000), baData.mid(0, 10000));
    resultTimeBigraph->addBackSeriesPoint(time.mid(0, 10000), baData.mid(0, 10000));
    resultTimeBigraph->adjustAxisRanges();

    // 对baData数据进行处理，进行FFT


    // 频域图
    resultFreqBigraph = new Bigraph(ui->upGraph);
    resultFreqBigraph->frontAxisX->setLabel("f[Hz]");
    resultFreqBigraph->frontAxisY->setLabel("v[mm/s]");
    resultFreqBigraph->adjustAxisRanges();
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
