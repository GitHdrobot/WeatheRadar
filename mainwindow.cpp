#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*获取显示设备可用的分辨率*/
    QDesktopWidget *dwsktopwidget = QApplication::desktop();
    QRect deskrect = dwsktopwidget->availableGeometry();
    //QRect screenrect = dwsktopwidget->screenGeometry();
    dispDev.setWidth(deskrect.width());
    dispDev.setHeight(deskrect.height());

    ui->setupUi(this);
    connect(ui->menuParaSetting,SIGNAL(aboutToShow()),this,SLOT(paraSetSlot()));
    connect(ui->action4_Pic,SIGNAL(triggered()),this,SLOT(dispFourPicSlot()));
    this->resize(dispDev.width,dispDev.height);
    /*
        this->setMaximumHeight(dispDev.height);
        this->setMaximumWidth(dispDev.width);
        this->setMinimumHeight(dispDev.height);
        this->setMinimumWidth(dispDev.width);
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paraSetSlot()
{
    //qDebug( "my icon size = %x", this->iconSize() );
    DialogSetting *dlgSetUi = new DialogSetting();
    dlgSetUi->setFocus();
    dlgSetUi->setModal(true);
    dlgSetUi->show();
}

void MainWindow::dispFourPicSlot()
{
    //qDebug( "my icon size = %x",4 );
}

//void MainWindow::paintEvent(QPaintEvent *)
//{
//    ui->widgetDisplay->update();
//}
