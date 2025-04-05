#include <cmath>
#include <vector>
#include "signalgenerator2.h"

// 设置频率
void SignalGenerator2::setFrequency(double hz)
{
    if(hz <= 0)
        throw std::invalid_argument("频率必须大于0");
    m_frequency = hz;
    updateParameters();
}

// 设置幅度
void SignalGenerator2::setAmplitude(double amp)
{
    if(amp <= 0)
        throw std::invalid_argument("幅度必须大于0");
    m_amplitude = amp;
}

// 设置采样率
void SignalGenerator2::setSampleRate(double fs)
{
    if(fs <= 0)
        throw std::invalid_argument("采样率必须大于0");
    m_sampleRate = fs;
    updateParameters();
}

int SignalGenerator2::requiredParameters() const
{
    return 2;
}

// 正弦波
SineWaveGenerator::SineWaveGenerator(double phaseShift) : m_phaseShift(phaseShift)
{
}

// 生成正弦波
std::vector<double> SineWaveGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);
    const double angleStep = 2 * M_PI * m_frequency / m_sampleRate;

    for(int i = 0; i < numSamples; ++i)
    {
        waveform.push_back(m_amplitude * std::sin(m_phaseShift + i * angleStep));
    }
    return waveform;
}

// 设置相位
void SineWaveGenerator::setPhaseShift(double phase)
{
    m_phaseShift = phase;
}

const char* SineWaveGenerator::waveformName() const
{
    return "Sine Wave";
}

int SineWaveGenerator::requiredParameters() const
{
    return 3;
}

SquareWaveGenerator::SquareWaveGenerator(double dutyCycle) : m_dutyCycle(dutyCycle)
{
}

std::vector<double> SquareWaveGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);
    const double T        = 1.0 / m_frequency;
    const double highTime = T * m_dutyCycle;

    for(int i = 0; i < numSamples; ++i)
    {
        double t            = static_cast<double>(i) / m_sampleRate;
        double timeInPeriod = std::fmod(t, T);
        waveform.push_back(timeInPeriod < highTime ? m_amplitude : -m_amplitude);
    }
    return waveform;
}

void SquareWaveGenerator::setDutyCycle(double dutyCycle)
{
    if(dutyCycle < 0 || dutyCycle > 1)
        throw std::invalid_argument("占空比必须在0-1之间");
    m_dutyCycle = dutyCycle;
}

const char* SquareWaveGenerator::waveformName() const
{
    return "Square Wave";
}

int SquareWaveGenerator::requiredParameters() const
{
    return 3;
}

TriangleWaveGenerator::TriangleWaveGenerator(double symmetry) : m_symmetry(symmetry)
{
    if(symmetry < 0 || symmetry > 1)
    {
        throw std::invalid_argument("对称系数必须在0到1之间");
    }
}

std::vector<double> TriangleWaveGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);

    const double period   = 1.0 / m_frequency;
    const double riseTime = period * m_symmetry;
    const double fallTime = period - riseTime;

    for(int i = 0; i < numSamples; ++i)
    {
        const double t = fmod(static_cast<double>(i) / m_sampleRate, period);

        if(t < riseTime)
        {
            // 上升阶段
            waveform.push_back(-m_amplitude + (t / riseTime) * 2 * m_amplitude);
        } else
        {
            // 下降阶段
            const double fallPos = (t - riseTime) / fallTime;
            waveform.push_back(m_amplitude - fallPos * 2 * m_amplitude);
        }
    }
    return waveform;
}

void TriangleWaveGenerator::setSymmetry(double symmetry)
{
    if(symmetry < 0 || symmetry > 1)
    {
        throw std::invalid_argument("对称系数必须在0到1之间");
    }
    m_symmetry = symmetry;
}

const char* TriangleWaveGenerator::waveformName() const
{
    return "Triangle Wave";
}

int TriangleWaveGenerator::requiredParameters() const
{
    return 3;  // 频率 + 幅度 + 对称系数
}

SawtoothWaveGenerator::SawtoothWaveGenerator(bool rising) : m_rising(rising)
{
}

std::vector<double> SawtoothWaveGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);

    const double period = 1.0 / m_frequency;

    for(int i = 0; i < numSamples; ++i)
    {
        const double t     = fmod(static_cast<double>(i) / m_sampleRate, period);
        const double phase = t / period;

        if(m_rising)
        {
            waveform.push_back(-m_amplitude + 2 * m_amplitude * phase);
        } else
        {
            waveform.push_back(m_amplitude - 2 * m_amplitude * phase);
        }
    }
    return waveform;
}

void SawtoothWaveGenerator::setRising(bool rising)
{
    m_rising = rising;
}

const char* SawtoothWaveGenerator::waveformName() const
{
    return m_rising ? "Rising Sawtooth" : "Falling Sawtooth";
}

int SawtoothWaveGenerator::requiredParameters() const
{
    return 3;  // 频率 + 幅度 + 波形方向
}

std::vector<double> WhiteNoiseGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);
    std::uniform_real_distribution<double> dist(-m_amplitude, m_amplitude);

    for(int i = 0; i < numSamples; ++i)
    {
        waveform.push_back(dist(m_rng));
    }
    return waveform;
}

const char* WhiteNoiseGenerator::waveformName() const
{
    return "White Noise";
}

UnbalanceVibrationGenerator::UnbalanceVibrationGenerator(int harmonics) : m_harmonics(harmonics)
{
    calculateHarmonics();
}

void UnbalanceVibrationGenerator::setRotationSpeed(double rpm)
{
    if(rpm <= 0)
        throw std::invalid_argument("转速必须大于0");
    m_rpm = rpm;
    updateParameters();
}

void UnbalanceVibrationGenerator::setUnbalanceMass(double kg)
{
    if(kg <= 0)
        throw std::invalid_argument("质量必须大于0");
    m_mass = kg;
    calculateHarmonics();
}

void UnbalanceVibrationGenerator::setPhaseOffset(double degrees)
{
    m_phaseOffset = degrees * M_PI / 180.0;  // 转为弧度
}

const char* UnbalanceVibrationGenerator::waveformName() const
{
    return "Unbalance Vibration";
}

std::vector<double> UnbalanceVibrationGenerator::generate(int numSamples)
{
    std::vector<double> waveform;
    waveform.reserve(numSamples);

    const double baseFreq = m_rpm / 60.0;  // 转频(Hz)
    const double dt       = 1.0 / m_sampleRate;

    for(int i = 0; i < numSamples; ++i)
    {
        double t     = i * dt;
        double value = 0.0;

        // 基频+谐波合成
        for(int n = 1; n <= m_harmonics; ++n)
        {
            double amp   = m_amplitude * m_harmonicWeights[n - 1];
            double phase = m_phaseOffset * n;
            value += amp * sin(2 * M_PI * n * baseFreq * t + phase);
        }
        waveform.push_back(value);
    }
    return waveform;
}

void UnbalanceVibrationGenerator::calculateHarmonics()
{
    m_harmonicWeights.resize(m_harmonics);
    // 简化的谐波权重模型（可根据实际物理模型修改）
    for(int i = 0; i < m_harmonics; ++i)
    {
        m_harmonicWeights[i] = 1.0 / (i + 1) * exp(-0.2 * i) * m_mass;
    }
}

// 工厂方法
std::unique_ptr<SignalGenerator2> SignalFactory::create(WaveformType type)
{
    switch(type)
    {
        case SINE:
            return std::make_unique<SineWaveGenerator>();
        case SQUARE:
            return std::make_unique<SquareWaveGenerator>();
        case TRIANGLE:
            return std::make_unique<TriangleWaveGenerator>();
        case SAWTOOTH:
            return std::make_unique<SawtoothWaveGenerator>();
        case UNBALANCE_VIBRATION:
            return std::make_unique<UnbalanceVibrationGenerator>();
        default:
            throw std::invalid_argument("未知的波形类型");
    }
}