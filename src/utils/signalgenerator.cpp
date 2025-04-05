#include "signalgenerator.h"
#include <memory>

SignalGenerator::SignalGenerator(QObject *parent) : QObject(parent)
{
}

void SignalGenerator::configure(qreal frequency, qreal amplitude, qreal sampleRate)
{
    Q_ASSERT_X(frequency > 0, "configure", "Frequency must be positive");
    Q_ASSERT_X(amplitude > 0, "configure", "Amplitude must be positive");
    Q_ASSERT_X(sampleRate > 0, "configure", "Sample rate must be positive");

    m_frequency  = frequency;
    m_amplitude  = amplitude;
    m_sampleRate = sampleRate;
    emit parametersChanged();
}

SineGenerator::SineGenerator(QObject *parent) : SignalGenerator(parent)
{
}

QVector<qreal> SineGenerator::generate(int numSamples)
{
    QVector<qreal> waveform;
    waveform.reserve(numSamples);

    const qreal angularFreq = 2 * M_PI * m_frequency;
    const qreal timeStep    = 1.0 / m_sampleRate;

    for(int i = 0; i < numSamples; ++i)
    {
        waveform.append(m_amplitude * qSin(angularFreq * i * timeStep + m_phase));
    }

    m_phase = std::fmod(m_phase + angularFreq * numSamples * timeStep, 2 * M_PI);
    return waveform;
}

SquareGenerator::SquareGenerator(QObject *parent) : SignalGenerator(parent)
{
}

void SquareGenerator::setDutyCycle(qreal newDutyCycle)
{
    newDutyCycle = qBound(0.0, newDutyCycle, 1.0);
    if(qFuzzyCompare(m_dutyCycle, newDutyCycle))
        return;

    m_dutyCycle = newDutyCycle;
    emit dutyCycleChanged();
}

QVector<qreal> SquareGenerator::generate(int numSamples)
{
    QVector<qreal> waveform;
    waveform.reserve(numSamples);

    const qreal period   = 1.0 / m_frequency;
    const qreal highTime = period * m_dutyCycle;

    for(int i = 0; i < numSamples; ++i)
    {
        const qreal t       = i / m_sampleRate;
        const qreal modTime = std::fmod(t, period);
        waveform.append((modTime < highTime) ? m_amplitude : -m_amplitude);
    }

    return waveform;
}

GeneratorFactory::GeneratorFactory(QObject *parent) : QObject(parent)
{
}

std::unique_ptr<SignalGenerator> GeneratorFactory::createGenerator(WaveformType type, QObject *parent)
{
    switch(type)
    {
        case SINE_WAVE:
            return std::make_unique<SineGenerator>(parent);
        case SQUARE_WAVE:
            return std::make_unique<SquareGenerator>(parent);
        // 添加其他波形...
        default:
            return nullptr;
    }
}