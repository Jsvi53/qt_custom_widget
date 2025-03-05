// schenckmain.h
#ifndef SCHENCKMAIN_H
#define SCHENCKMAIN_H

#include <QWidget>

namespace Ui {
class SchenckMain;
}

class SchenckMain : public QWidget {
    Q_OBJECT

public:
    explicit SchenckMain(QWidget *parent = nullptr);
    ~SchenckMain();

signals:
    void showSubInterface();

private:
    Ui::SchenckMain *ui;
};

#endif // SCHENCKMAIN_H