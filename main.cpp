#include "mainwindow.h"
#include <QApplication>

RVP900 rvp9;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
