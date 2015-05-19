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
    connect(ui->doubleSpinBoxAzimuth,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxAzimuth_valueChanged(double));
            connect(ui->doubleSpinBoxElevation,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxElevation_valueChanged(double));
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



    /*对串口进行设置*/
    serialPort.setPortName(TTY_DEV4);
    serialPort.setBaudRate(BAUD38400);
    serialPort.setFlowControl(FLOW_XONXOFF);
    serialPort.setParity(PAR_NONE);
    serialPort.setDataBits(DATA_8);
    serialPort.setStopBits(STOP_1);

    /*多普勒滤波器选项添加*/
    ui->comboBoxDopFilter->addItem("None");
    ui->comboBoxDopFilter->addItem("1");
    ui->comboBoxDopFilter->addItem("2");
    ui->comboBoxDopFilter->addItem("3");
    ui->comboBoxDopFilter->addItem("4");
    ui->comboBoxDopFilter->addItem("5");
    ui->comboBoxDopFilter->addItem("6");
    ui->comboBoxDopFilter->addItem("7");

    /*脉宽选项添加*/
    ui->comboBoxPulseWidth->addItem(tr("1us"));
    ui->comboBoxPulseWidth->addItem(tr("5us"));
    ui->comboBoxPulseWidth->addItem(tr("10us"));
    ui->comboBoxPulseWidth->addItem(tr("20us"));

    /*脉冲重复频率选项添加*/
    ui->comboBoxPRF->addItem("300");
    ui->comboBoxPRF->addItem("500");
    ui->comboBoxPRF->addItem("1000");
    ui->comboBoxPRF->addItem("2000");
    ui->comboBoxPRF->addItem("3000");
    ui->comboBoxPRF->addItem("4000");
    ui->comboBoxPRF->addItem("5000");

    /*双脉冲重复比选项添加*/
    ui->comboBoxDPrf->addItem("None");
    ui->comboBoxDPrf->addItem("2:3");
    ui->comboBoxDPrf->addItem("3:4");
    ui->comboBoxDPrf->addItem("4:5");

    /*扫描距离 选项添加*/
    ui->comboBoxLmsk->addItem("10KM");
    ui->comboBoxLmsk->addItem("20KM");
    ui->comboBoxLmsk->addItem("30KM");
    ui->comboBoxLmsk->addItem("50KM");
    ui->comboBoxLmsk->addItem("150KM");
    ui->comboBoxLmsk->addItem("300KM");

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

//处理 打开发射按钮 发出的点击信号
void MainWindow::on_pbtnOpenTransmit_clicked()
{
    char Openbuf[]={0x54,0x01,0xAA,0x01,0};
    serialPort.write(Openbuf);
    serialPort.read(rvp9.trstatus,8);
    //改变相关显示状态
}
//处理 关闭发射按钮 发出的点击信号
void MainWindow::on_pbtnCloseTransmit_clicked()
{
    char Closebuf[]={0x54,0x01,0x55,0x56,0};
    serialPort.write(Closebuf);
    serialPort.read(rvp9.trstatus,8);
    //改变相关显示状态
}
//处理 天线扫描按钮 发出的点击信号
void MainWindow::on_pbtnSweep_clicked()
{
    //使 停止扫描按钮 使能
    ui->pbtnStopSweep->setEnabled(true);
    //此处的天线扫描不明白
    char c;
    float eng;
    int ieng;
    rvp9.elevation=elDisplay_spinbox->value();
    if (antenna_el>=0)
        eng=antenna_el*4096.0/360.0;
    else
        eng=(360+antenna_el)*4096.0/360.0;
    ieng=eng;
    Abuf[4]=ieng%256;
    Abuf[5]=ieng/256;
    c=Abuf[0]+Abuf[1]+Abuf[2]+Abuf[3]+Abuf[4]+Abuf[5];
    Abuf[6]=0-c;
    PortSend(serial_fd,Abuf,7);
    if(M!=-1)
    {
        collect_Slot();
    }
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
    /*扫描距离 改变  距离掩码相关*/
void MainWindow::on_comboBoxLmsk_activated(int index)
{
    if(0 == index){
        rvp9.disRange = rvp9.RANGE_10;
    }else if(1 == index){
        rvp9.disRange = rvp9.RANGE_20;
    }else if(2 == index){
         rvp9.disRange = rvp9.RANGE_30;
    }else if(3 == index){
        rvp9.disRange = rvp9.RANGE_50;
   }else if(4 == index){
        rvp9.disRange = rvp9.RANGE_150;
   }else if(5 == index){
        rvp9.disRange = rvp9.RANGE_300;
   }
}
/*RPF 脉冲重复频率 改变*/
void MainWindow::on_comboBoxPRF_activated(int index)
{
    if(0 == index){
        rvp9.PRF = 300;
    }else if(1 == index){
        rvp9.PRF = 500;
    }else if(2 == index){
        rvp9.PRF = 1000;
    }else if(3 == index){
        rvp9.PRF = 2000;
    }else if(4 == index){
        rvp9.PRF = 3000;
    }else if(5 == index){
        rvp9.PRF = 4000;
    }else if(6 == index){
        rvp9.PRF = 5000;
    }
}
/*双脉冲重复比 改变   改变后仍需对PROC命令的8、9位进行设置*/
void MainWindow::on_comboBoxDPrf_activated(int index)
{
    if(0 == index){
        rvp9.PRF_Ratio =DPRF_NONE;
    }else if(1 == index){
        rvp9.PRF_Ratio =DPRF_2TO3;
    }else if(2 == index){
        rvp9.PRF_Ratio =DPRF_3TO4;
    }else if(3 == index){
        rvp9.PRF_Ratio =DPRF_4TO5;
    }
}
/*脉宽  改变*/
void MainWindow::on_comboBoxPulseWidth_activated(int index)
{
    if(0 == index){
        rvp9.pulseWidth = 1;
    }else if(1 == index){
        rvp9.pulseWidth = 5;
    }else if(2 == index){
        rvp9.pulseWidth = 10;
    }else if(3 == index){
        rvp9.pulseWidth = 20;
    }
}
/*多普勒滤波器  改变*/
void MainWindow::on_comboBoxDopFilter_activated(int index)
{
    rvp9.dopFilter = index;
}
/*设置方位角角度*/
void MainWindow::on_doubleSpinBoxAzimuth_valueChanged(double arg1)
{
    rvp9.azimuth = arg1;
}
/*设置仰角角度*/
void MainWindow::on_doubleSpinBoxElevation_valueChanged(double arg1)
{
    rvp9.elevation = arg1;
}

int MainWindow::initMainWindow(){

}
