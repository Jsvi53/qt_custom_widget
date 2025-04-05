#include <QStackedWidget>
#include "balancemeasurescreeen.h"
#include "filemanagerscreen.h"

class MainWidget : public QStackedWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    FileManagerScreen *managerScreen;
    BalanceMeasureScreen *balanceMeasureScreen;

private slots:
    // 当managerScreen中的item 被按下时
    void onPushButtonPressed();


};

