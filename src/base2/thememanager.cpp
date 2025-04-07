// thememanager.cpp
#include "thememanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

ThemeManager& ThemeManager::instance()
{
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager(QObject* parent) : QObject(parent)
{
    // 初始化默认配置
    m_shadowConfigs["default"] = ShadowConfig(QColor(43,43,43), 30, QPoint(0,5));
    m_shadowConfigs["navigation"] = ShadowConfig(QColor(43,43,43), 30, QPoint(0,5));
    m_shadowConfigs["workarea"] = ShadowConfig(QColor(43,43,43), 10, QPoint(5,5));
}

void ThemeManager::registerWidget(QWidget* widget, const QString& configName)
{
    if(widget && m_shadowConfigs.contains(configName)){
        m_registeredWidgets.insert(widget, configName);
        applyShadowEffect(widget, configName);
    }
}

void ThemeManager::applyTheme(const QString& themeName)
{
    loadThemeConfig(themeName);

    // 更新所有已注册控件
    QHashIterator<QWidget*, QString> it(m_registeredWidgets);
    while (it.hasNext()) {
        it.next();
        applyShadowEffect(it.key(), it.value());
    }

    emit themeChanged();
}

void ThemeManager::loadThemeConfig(const QString& themePath)
{
    QFile file(themePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Theme file not found:" << themePath;
        return;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return;
    }

    QJsonObject root = doc.object();
    QJsonObject shadows = root["shadows"].toObject();

    foreach(const QString& key, shadows.keys()) {
        QJsonObject config = shadows[key].toObject();
        ShadowConfig sc;
        sc.color = QColor(config["color"].toString());
        sc.radius = config["radius"].toDouble();
        QJsonArray offset = config["offset"].toArray();
        if (offset.size() >= 2) {
            sc.offset = QPoint(offset[0].toInt(), offset[1].toInt());
        }
        m_shadowConfigs[key] = sc;
    }
}

void ThemeManager::applyShadowEffect(QWidget* widget, const QString& configName)
{
    if (!m_shadowConfigs.contains(configName)) return;

    const ShadowConfig& config = m_shadowConfigs[configName];
    QGraphicsDropShadowEffect* effect = nullptr;

    if (widget->graphicsEffect()) {
        effect = qobject_cast<QGraphicsDropShadowEffect*>(widget->graphicsEffect());
    } else {
        effect = new QGraphicsDropShadowEffect(widget);
        widget->setGraphicsEffect(effect);
    }

    if (effect) {
        effect->setColor(config.color);
        effect->setBlurRadius(config.radius);
        effect->setOffset(config.offset);
    }
}

// QML属性访问
QColor ThemeManager::getShadowColor(const QString& configName) const
{
    return m_shadowConfigs.value(configName).color;
}

qreal ThemeManager::getShadowRadius(const QString& configName) const
{
    return m_shadowConfigs.value(configName).radius;
}

QPoint ThemeManager::getShadowOffset(const QString& configName) const
{
    return m_shadowConfigs.value(configName).offset;
}