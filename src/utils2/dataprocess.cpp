#include <Eigen/Dense>
#include <cmath>
#include <complex>

#include "dataprocess.h"


void performFFT(const QVector<double>& data, double Fs, QVector<double>& freq, QVector<double>& fftMagnitude)
{
    int             N = data.size();
    Eigen::VectorXd timeData(N);
    for(int i = 0; i < N; ++i)
    {
        timeData(i) = data[i];
    }

    // 使用 Eigen 进行 FFT
    Eigen::FFT<double> fft;
    Eigen::VectorXcd   fftResult(N);
    fft.fwd(fftResult, timeData);

    // 计算频率轴
    freq.resize(N / 2);
    for(int i = 0; i < N / 2; ++i)
    {
        freq[i] = i * Fs / N;
    }

    // 计算幅值
    fftMagnitude.resize(N / 2);
    for(int i = 0; i < N / 2; ++i)
    {
        fftMagnitude[i] = std::abs(fftResult(i)) / N;
    }
}