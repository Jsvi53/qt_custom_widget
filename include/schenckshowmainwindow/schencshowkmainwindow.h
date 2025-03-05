#ifndef SCHENCSHOWKMAINWINDOW_H
#define SCHENCSHOWKMAINWINDOW_H

#include <QWidget>

namespace Ui {
class SchencShowkMainWindow;
}

class SchencShowkMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SchencShowkMainWindow(QWidget *parent = nullptr);
    ~SchencShowkMainWindow();

private:
    Ui::SchencShowkMainWindow *ui;
};

#endif // SCHENCSHOWKMAINWINDOW_H
