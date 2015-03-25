#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pRVP900 = &RVP900.getRVP900Ins();
    ui->setupUi(this);

   //QAction  *act = new QAction("seeting",this);
   //ui->menuParaSetting->addAction(act);
    connect(ui->menuParaSetting,SIGNAL(aboutToShow()),this,SLOT(paraSetSlot()));
    //connect(ui->menuParaSetting,SIGNAL(aboutToHide()),this,SLOT(paraSetSlot()));
    connect(ui->action4_Pic,SIGNAL(triggered()),this,SLOT(dispFourPicSlot()));
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
