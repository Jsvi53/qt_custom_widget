// TCHRT.cpp
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

#include "tchrt.h"


TCHRT::TCHRT(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 创建三个绘图区域
    QCustomPlot *plotBA = new QCustomPlot(this);
    QCustomPlot *plotDE = new QCustomPlot(this);
    QCustomPlot *plotFE = new QCustomPlot(this);

    layout->addWidget(plotBA);
    layout->addWidget(plotDE);
    layout->addWidget(plotFE);

    // 加载CSV数据
    QVector<double> baData, deData, feData;
    loadCSVData("F:/code/projects/29_QT_projects/jpbalance/database/12k_144.csv", baData, deData, feData);

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

    // 配置BA通道绘图
    plotBA->addGraph();
    plotBA->graph(0)->setData(time, baData);
    plotBA->xAxis->setLabel("Time (s)");
    plotBA->yAxis->setLabel("Amplitude");
    plotBA->xAxis->rescale();
    plotBA->yAxis->rescale();
    plotBA->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // 配置DE通道绘图
    plotDE->addGraph();
    plotDE->graph(0)->setData(time, deData);
    plotDE->xAxis->setLabel("Time (s)");
    plotDE->yAxis->setLabel("Amplitude");
    plotDE->xAxis->rescale();
    plotDE->yAxis->rescale();
    plotDE->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // 配置FE通道绘图
    plotFE->addGraph();
    plotFE->graph(0)->setData(time, feData);
    plotFE->graph(0)->setData(time, feData);
    plotFE->xAxis->setLabel("Time (s)");
    plotFE->yAxis->setLabel("Amplitude");
    plotFE->xAxis->rescale();
    plotFE->yAxis->rescale();
    plotFE->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void TCHRT::loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData)
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

TCHRT2::TCHRT2(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 创建三个绘图区域
    QCustomPlot *plotBA = new QCustomPlot(this);

    layout->addWidget(plotBA);

    // 加载CSV数据
    QVector<double> baData, deData, feData;
    loadCSVData("F:/code/projects/29_QT_projects/jpbalance/database/12k_144.csv", baData, deData, feData);

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

    // 配置BA通道绘图
    plotBA->addGraph();
    plotBA->graph(0)->setData(time, baData);
    plotBA->xAxis->setLabel("Time (s)");
    plotBA->yAxis->setLabel("Amplitude");
    plotBA->xAxis->rescale();
    plotBA->yAxis->rescale();
    plotBA->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void TCHRT2::loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData)
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


TCHRT3::TCHRT3(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 创建一个新的绘图区域
    QCustomPlot *plotBA = new QCustomPlot(this);

    layout->addWidget(plotBA);

    // 加载CSV数据
    QVector<double> baData, deData, feData;
    loadCSVData("F:/code/projects/29_QT_projects/jpbalance/database/12k_144.csv", baData, deData, feData);

    if (baData.isEmpty() || deData.isEmpty() || feData.isEmpty()) {
        qDebug() << "数据加载失败或为空！";
        return;
    }

    // 配置BA通道绘图
    int N = baData.size();
    QVector<double> time(N);
    const double Fs = 12000.0;
    for (int i = 0; i < N; ++i) time[i] = i / Fs;

    plotBA->addGraph();
    plotBA->graph(0)->setData(time, baData);
    plotBA->xAxis->setLabel("Time (s)");
    plotBA->yAxis->setLabel("Amplitude");
    plotBA->xAxis->rescale();
    plotBA->yAxis->rescale();
    plotBA->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void TCHRT3::loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << filePath;
        return;
    }

    QTextStream in(&file);
    int lineCount = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (lineCount++ == 0)
            continue;  // 跳过标题行

        QStringList parts = line.split(',');
        if (parts.size() >= 3) {
            bool ok[3];
            double ba = parts[0].toDouble(&ok[0]);
            double de = parts[1].toDouble(&ok[1]);
            double fe = parts[2].toDouble(&ok[2]);

            if (ok[0] && ok[1] && ok[2]) {
                baData.append(ba);
                deData.append(de);
                feData.append(fe);
            } else {
                qDebug() << "行" << lineCount << "数据转换错误";
            }
        } else {
            qDebug() << "行" << lineCount << "数据不完整";
        }
    }
    file.close();
}


