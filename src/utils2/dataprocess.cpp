#include <Eigen/Dense>
#include <cmath>
#include <complex>

#include "dataprocess.h"

inline void performFFT(const QVector<double>& data, double Fs, QVector<double>& freq, QVector<double>& fftMagnitude)
{
    int N = data.size();

    // 将实数数据转换为复数数据
    Eigen::VectorXcd timeData(N);
    for(int i = 0; i < N; ++i)
    {
        timeData(i) = std::complex<double>(data[i], 0.0);
    }

    // 使用 Eigen 进行 FFT
    Eigen::FFT<double> fft;
    Eigen::VectorXcd   fftResult(N);
    fft.fwd(fftResult, timeData);

    // 计算频率轴
    freq.resize(N / 2 + 1);  // 由于对称性，只需要一半的频率
    for(int i = 0; i < N / 2 + 1; ++i)
    {
        freq[i] = i * Fs / N;
    }

    // 计算幅值
    fftMagnitude.resize(N / 2 + 1);  // 由于对称性，只需要一半的幅值
    for(int i = 0; i < N / 2 + 1; ++i)
    {
        fftMagnitude[i] = std::abs(fftResult(i)) / N;
    }
}