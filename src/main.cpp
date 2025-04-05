#include <QApplication>
#include <QDebug>

#include "TCHRT.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TCHRT w;
    w.show();

    return a.exec();
}
