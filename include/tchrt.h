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