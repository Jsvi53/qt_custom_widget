// TCHRT.h
#pragma once

#include <QVector>
#include <QWidget>

#include "qcustomplot.h"


class TCHRT : public QWidget
{
    Q_OBJECT
public:
    explicit TCHRT(QWidget *parent = nullptr);

private:
    void loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData);
};




class TCHRT2 : public QWidget
{
    Q_OBJECT
public:
    explicit TCHRT2(QWidget *parent = nullptr);

private:
    void loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData);
};

class TCHRT3 : public QWidget
{
    Q_OBJECT

public:
    explicit TCHRT3(QWidget *parent = nullptr);
    void loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData);

private:
    void setupPlot();
};




class TCHRT4 : public QWidget
{
    Q_OBJECT
public:
    explicit TCHRT4(QWidget *parent = nullptr);
};
