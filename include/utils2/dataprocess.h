#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__
#include <QVector>

void performFFT(const QVector<double>& data, double Fs, QVector<double>& freq, QVector<double>& fftMagnitude);




#endif // __DATAPROCESS_H__