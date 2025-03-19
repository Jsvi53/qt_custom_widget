/***
 * @Date: 2025-03-19 22:48:56
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-19 23:00:53
 * @FilePath: \qt_custom_widget\include\utils\signalgenerator.h
 */
#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#include <QObject>
#include <QVector>
#include <QtMath>
#include <memory>

class SignalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SignalGenerator(QObject *parent = nullptr);

    // 公共参数配置接口
    Q_INVOKABLE virtual void           configure(qreal frequency, qreal amplitude, qreal sampleRate);
    Q_INVOKABLE virtual QVector<qreal> generate(int numSamples) = 0;

    // 波形元信息
    Q_INVOKABLE virtual QString waveformName() const = 0;
    Q_INVOKABLE virtual int     waveformId() const   = 0;

signals:
    void parametersChanged();

protected:
    qreal m_frequency  = 1000.0;   // Hz
    qreal m_amplitude  = 1.0;      // Peak-to-peak
    qreal m_sampleRate = 44100.0;  // Hz
};

// SineGenerator
class SineGenerator : public SignalGenerator
{
    Q_OBJECT
public:
    explicit SineGenerator(QObject *parent = nullptr);

    QVector<qreal> generate(int numSamples) Q_DECL_OVERRIDE;
    QString        waveformName() const Q_DECL_OVERRIDE
    {
        return tr("Sine Wave");
    }
    int waveformId() const Q_DECL_OVERRIDE
    {
        return 0;
    }

private:
    qreal m_phase = 0.0;
};

// 方波
class SquareGenerator : public SignalGenerator
{
    Q_OBJECT
public:
    explicit SquareGenerator(QObject *parent = nullptr);

    QVector<qreal> generate(int numSamples) Q_DECL_OVERRIDE;
    QString        waveformName() const Q_DECL_OVERRIDE
    {
        return tr("Square Wave");
    }
    int waveformId() const Q_DECL_OVERRIDE
    {
        return 1;
    }

    Q_PROPERTY(qreal dutyCycle READ dutyCycle WRITE setDutyCycle NOTIFY dutyCycleChanged)
    qreal dutyCycle() const
    {
        return m_dutyCycle;
    }
    void setDutyCycle(qreal newDutyCycle);

signals:
    void dutyCycleChanged();

private:
    qreal m_dutyCycle = 0.5;  // 占空比 0.0-1.0
};

// 工厂类
class GeneratorFactory : public QObject
{
    Q_OBJECT
public:
    enum WaveformType { SINE_WAVE = 0, SQUARE_WAVE = 1, TRIANGLE_WAVE = 2, SAWTOOTH_WAVE = 3 };
    Q_ENUM(WaveformType)

    explicit GeneratorFactory(QObject *parent = nullptr);

    Q_INVOKABLE static std::unique_ptr<SignalGenerator> createGenerator(WaveformType type, QObject *parent = nullptr);
};

#endif  // SIGNALGENERATOR_H