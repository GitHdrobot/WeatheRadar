#include "mainwindow.h"
#include <QApplication>

RVP900 rvp9;//rvp9控制对象
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
