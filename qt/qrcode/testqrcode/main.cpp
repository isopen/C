#include "mainwindow.h"
#include <QApplication>
#include <QZXing.h>

int main(int argc, char *argv[])
{
    QZXing::registerQMLTypes();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
