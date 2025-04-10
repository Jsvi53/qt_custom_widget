#include <QApplication>
#include <QDebug>
#include <QQmlEngine>
#include <QVector>

#include "newmachinetemplate.h"

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

    qRegisterMetaType<QVector<double>>("QVector<double>");      // 注册QVector<double>类型到元对象系统

    // CommonPropertyItem w(nullptr, true);
    // w.setTitle("名称");
    // w.setProperty("机车");
    // w.addListItems(QVector<QString>{"机车1", "机车2", "机车3"});
    NewMachineTemplateScreen w;
    w.show();

    return a.exec();
}
