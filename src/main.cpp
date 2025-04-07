#include <QApplication>
#include <QDebug>
#include <QQmlEngine>
#include <QVector>

#include "resultgraph.h"
// #include "thememanager.h"
// #include "tchrt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
        // 初始化主题（全局应用）
        ThemeManager::instance().applyTheme("F:/code/projects/29_QT_projects/custom_widget/config2/theme/dark.json");
        // 注册QML类型（如果用到QML）
        qmlRegisterSingletonType<ThemeManager>("App.Theme", 1, 0, "ThemeManager", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return &ThemeManager::instance();
        });
    */
    ResultGraph w;
    w.show();

    return a.exec();
}
