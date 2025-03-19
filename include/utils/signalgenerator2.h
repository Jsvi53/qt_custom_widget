#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

class SignalGenerator2
{
public:
    virtual ~SignalGenerator2() = default;

    // 基础参数配置
    virtual void setFrequency(double hz);
    virtual void setAmplitude(double amp);
    virtual void setSampleRate(double fs);

    // 波形生成核心接口
    virtual std::vector<double> generate(int numSamples) = 0;

    // 元信息
    virtual const char* waveformName() const = 0;
    virtual int         requiredParameters() const;

protected:
    double m_frequency  = 1000.0;
    double m_amplitude  = 1.0;
    double m_sampleRate = 44100.0;

    virtual void updateParameters()
    {
    }
};

class SineWaveGenerator : public SignalGenerator2
{
public:
    explicit SineWaveGenerator(double phaseShift = 0.0);
    std::vector<double> generate(int numSamples) override;
    void                setPhaseShift(double phase);
    const char*         waveformName() const override;
    int                 requiredParameters() const override;

private:
    double m_phaseShift = 0.0;
};

class SquareWaveGenerator : public SignalGenerator2
{
public:
    explicit SquareWaveGenerator(double dutyCycle = 0.5);
    std::vector<double> generate(int numSamples) override;
    void                setDutyCycle(double dutyCycle);
    const char*         waveformName() const override;
    int                 requiredParameters() const override;

private:
    double m_dutyCycle;
};

class TriangleWaveGenerator : public SignalGenerator2
{
public:
    explicit TriangleWaveGenerator(double symmetry = 0.5);

    std::vector<double> generate(int numSamples) override;
    void                setSymmetry(double symmetry);
    const char*         waveformName() const override;
    int                 requiredParameters() const override;

private:
    double m_symmetry;  // 对称系数 (0.0~1.0)
};

class SawtoothWaveGenerator : public SignalGenerator2
{
public:
    explicit SawtoothWaveGenerator(bool rising = true);

    std::vector<double> generate(int numSamples) override;
    void                setRising(bool rising);
    const char*         waveformName() const override;
    int                 requiredParameters() const override;

private:
    bool m_rising;  // true=上升锯齿波, false=下降锯齿波
};

class WhiteNoiseGenerator : public SignalGenerator2
{
public:
    std::vector<double> generate(int numSamples) override;
    const char*         waveformName() const override;

private:
    std::mt19937 m_rng{std::random_device{}()};
};

class UnbalanceVibrationGenerator : public SignalGenerator2
{
public:
    explicit UnbalanceVibrationGenerator(int harmonics = 3);

    // 扩展参数接口
    void setRotationSpeed(double rpm);    // 设置转速(RPM)
    void setUnbalanceMass(double kg);     // 不平衡质量
    void setPhaseOffset(double degrees);  // 相位偏移

    std::vector<double> generate(int numSamples) override;
    const char*         waveformName() const override;

    // 动平衡特有功能
    std::vector<double> getHarmonicComponents() const;
    double              getCriticalSpeed() const;

private:
    void calculateHarmonics();  // 谐波成分计算

    double              m_rpm         = 3000.0;  // 转速
    double              m_mass        = 0.1;     // 不平衡质量(kg)
    double              m_phaseOffset = 0.0;     // 相位偏移(度)
    int                 m_harmonics;             // 谐波数量
    std::vector<double> m_harmonicWeights;       // 各次谐波权重
};

class VibrationAnalyzer
{
public:
    struct AnalysisResult {
        double mainFrequency;       // 主振动频率
        double amplitude;           // 幅值
        double phaseAngle;          // 相位角(度)
        double harmonicDistortion;  // 谐波失真率
    };

    static AnalysisResult analyze(const std::vector<double>& signal, double sampleRate, double rotationSpeed);
};

class BalanceCalculator
{
public:
    virtual ~BalanceCalculator() = default;

    // 计算配重方案
    virtual std::vector<double> calculateWeights(const std::vector<double>& vibrationData, const std::vector<double>& phaseData, double rotationSpeed) = 0;

    // 振动预测
    virtual std::vector<double> predictVibration(const std::vector<double>& weights) = 0;
};

class SignalFactory
{
public:
    enum WaveformType { SINE, SQUARE, TRIANGLE, SAWTOOTH, UNBALANCE_VIBRATION };

    static std::unique_ptr<SignalGenerator2> create(WaveformType type);
};