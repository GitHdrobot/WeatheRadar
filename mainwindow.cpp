#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rvp900.h"
extern RVP900 rvp9;

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
    connect(ui->doubleSpinBoxAzimuth,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxAzimuth_valueChanged(double)));
    connect(ui->doubleSpinBoxElevation,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxElevation_valueChanged(double)));
    connect(ui->pbtnOpenTransmit,SIGNAL(clicked()),SLOT(on_pbtnOpenTransmit_clicked()));
    connect(ui->pbtnCloseTransmit,SIGNAL(clicked()),SLOT(on_pbtnCloseTransmit_clicked()));
    connect(ui->pbtnSweep,SIGNAL(clicked()),SLOT(on_pbtnSweep_clicked()));
    connect(ui->pbtnStopSweep,SIGNAL(clicked()),SLOT(on_pbtnStopSweep_clicked()));
    connect(ui->pbtnAzimuth,SIGNAL(clicked()),SLOT(on_pbtnAzimuth_clicked()));
    connect(ui->pbtnElevation,SIGNAL(clicked()),SLOT(on_pbtnElevation_clicked()) );
    connect(ui->pbtnStop,SIGNAL(clicked()),SLOT(on_pbtnStop_clicked()) );
    connect(ui->pbtnCollect,SIGNAL(clicked()),SLOT(on_pbtnCollect_clicked()));
    connect(ui->comboBoxMode,SIGNAL(activated(int)),SLOT(on_comboBoxMode_activated(int)));
    connect(ui->comboBoxLmsk,SIGNAL(activated(int)),SLOT(on_comboBoxLmsk_activated(int)));
    connect(ui->comboBoxPRF,SIGNAL(activated(int)),SLOT(on_comboBoxPRF_activated(int)));
    connect(ui->comboBoxDPrf,SIGNAL(activated(int)),SLOT(on_comboBoxDPrf_activated(int)));
    connect(ui->comboBoxPulseWidth,SIGNAL(activated(int)),SLOT(on_comboBoxPulseWidth_activated(int)));
    connect(ui->comboBoxDopFilter,SIGNAL(activated(int)),SLOT(on_comboBoxDopFilter_activated(int)));

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

void MainWindow::on_pbtnOpenTransmit_clicked()
{
    //处理 打开发射按钮 发出的点击信号
}

void MainWindow::on_pbtnCloseTransmit_clicked()
{
    //处理 关闭发射按钮 发出的点击信号
}

void MainWindow::on_pbtnSweep_clicked()
{
    //处理 天线扫描按钮 发出的点击信号
}

void MainWindow::on_pbtnStopSweep_clicked()
{
    //处理 天线停止扫描按钮 发出的点击信号
}

void MainWindow::on_pbtnAzimuth_clicked()
{
    //方位定位
}

void MainWindow::on_pbtnElevation_clicked()
{
    //仰角定位
}

void MainWindow::on_pbtnStop_clicked()
{
   //停止采集
}

void MainWindow::on_pbtnCollect_clicked()
{
    //恢复采集
}


void MainWindow::on_comboBoxMode_activated(int index)
{
    //扫描方式  改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }
}

void MainWindow::on_comboBoxLmsk_activated(int index)
{
    //扫描距离 改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }
}

void MainWindow::on_comboBoxPRF_activated(int index)
{
    //RPF 脉冲重复频率 改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }
}

void MainWindow::on_comboBoxDPrf_activated(int index)
{
    //双脉冲重复比 改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }
}

void MainWindow::on_comboBoxPulseWidth_activated(int index)
{
    //脉宽  改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }

}

void MainWindow::on_comboBoxDopFilter_activated(int index)
{
    //多普勒滤波器  改变
    if(0 == index){

    }else if(1 == index){

    }else if(2 == index){

    }

}

void MainWindow::on_doubleSpinBoxAzimuth_valueChanged(double arg1)
{
     rvp9.azimuth = arg1;
}

void MainWindow::on_doubleSpinBoxElevation_valueChanged(double arg1)
{
    rvp9.elevation = arg1;
}

int MainWindow::initMainWindow(){

}
