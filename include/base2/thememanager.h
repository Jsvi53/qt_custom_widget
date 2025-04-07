// thememanager.h
#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QHash>
#include <QColor>
#include <QWidget>

class ThemeManager : public QObject
{
    Q_OBJECT
public:
    struct ShadowConfig {
        QColor color;
        qreal radius;
        QPoint offset;
        ShadowConfig(QColor c = Qt::black, qreal r = 0, QPoint o = QPoint()) 
            : color(c), radius(r), offset(o) {}
    };

    static ThemeManager& instance();

    // 注册控件并应用阴影
    void registerWidget(QWidget* widget, const QString& configName = "default");
    void applyTheme(const QString& themeName);

    // QML可访问接口
    Q_INVOKABLE QColor getShadowColor(const QString& configName = "default") const;
    Q_INVOKABLE qreal getShadowRadius(const QString& configName = "default") const;
    Q_INVOKABLE QPoint getShadowOffset(const QString& configName = "default") const;

signals:
    void themeChanged();

private:
    explicit ThemeManager(QObject* parent = nullptr);
    void loadThemeConfig(const QString& themePath);
    void applyShadowEffect(QWidget* widget, const QString& configName); // 私有方法声明

    QHash<QString, ShadowConfig> m_shadowConfigs;
    QHash<QWidget*, QString> m_registeredWidgets;
};

#endif // THEMEMANAGER_H