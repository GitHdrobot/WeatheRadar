#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rvp900.h"


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
    connect(ui->spinBoxAzimuthSet,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxAzimuth_valueChanged(double)));
    connect(ui->spinBoxElevationSet,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBoxElevation_valueChanged(double)));
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

    //    /*多普勒滤波器选项添加*/
    //    ui->comboBoxDopFilter->addItem("None");
    //    ui->comboBoxDopFilter->addItem("1");
    //    ui->comboBoxDopFilter->addItem("2");
    //    ui->comboBoxDopFilter->addItem("3");
    //    ui->comboBoxDopFilter->addItem("4");
    //    ui->comboBoxDopFilter->addItem("5");
    //    ui->comboBoxDopFilter->addItem("6");
    //    ui->comboBoxDopFilter->addItem("7");

    //    /*脉宽选项添加*/
    //    ui->comboBoxPulseWidth->addItem(tr("1us"));
    //    ui->comboBoxPulseWidth->addItem(tr("5us"));
    //    ui->comboBoxPulseWidth->addItem(tr("10us"));
    //    ui->comboBoxPulseWidth->addItem(tr("20us"));

    //    /*脉冲重复频率选项添加*/
    //    ui->comboBoxPRF->addItem("300");
    //    ui->comboBoxPRF->addItem("500");
    //    ui->comboBoxPRF->addItem("1000");
    //    ui->comboBoxPRF->addItem("2000");
    //    ui->comboBoxPRF->addItem("3000");
    //    ui->comboBoxPRF->addItem("4000");
    //    ui->comboBoxPRF->addItem("5000");

    //    /*双脉冲重复比选项添加*/
    //    ui->comboBoxDPrf->addItem("None");
    //    ui->comboBoxDPrf->addItem("2:3");
    //    ui->comboBoxDPrf->addItem("3:4");
    //    ui->comboBoxDPrf->addItem("4:5");

    //    /*扫描距离 选项添加*/
    //    ui->comboBoxLmsk->addItem("10KM");
    //    ui->comboBoxLmsk->addItem("20KM");
    //    ui->comboBoxLmsk->addItem("30KM");
    //    ui->comboBoxLmsk->addItem("50KM");
    //    ui->comboBoxLmsk->addItem("150KM");
    //    ui->comboBoxLmsk->addItem("300KM");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete rvp9;
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
    char openbuf[]={0x54,0x01,0xAA,0x01,0};
    serialPort.write(openbuf);
    serialPort.read(rvp9.trstatus,8);
    //改变相关显示状态
}
//处理 关闭发射按钮 发出的点击信号
void MainWindow::on_pbtnCloseTransmit_clicked()
{
    char closebuf[]={0x54,0x01,0x55,0x56,0};
    serialPort.write(closebuf);
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
    float elevationf;
    int elevationi;
    //获取天线的仰角大小
    rvp9.elevation=ui->spinBoxElevationSet->value();
    if (rvp9.elevation>=0){
        //乘以一个比例因子 将度转化为角码位数据 此处有12个角码位 即范围是0-4095
        elevationf=rvp9.elevation*4096.0/360.0;
    }
    else{//角度为负
        elevationf=(360+rvp9.elevation)*4096.0/360.0;
    }
    //强制转换
    elevationi = elevationf;
    //取得仰角低字节数据
    rvp9.antennaBuf[4]=elevationi % 256;
    //取得仰角高字节数据
    rvp9.antennaBuf[5]=elevationi / 256;
    c=rvp9.antennaBuf[0]+rvp9.antennaBuf[1]+rvp9.antennaBuf[2]+rvp9.antennaBuf[3]+rvp9.antennaBuf[4]+rvp9.antennaBuf[5];
    //作用不知道
    rvp9.antennaBuf[6]=0-c;
    //通过串口发送数据
    serialPort.write(rvp9.antennaBuf,7);
    if(true == rvp9.isWorking )
    {
        //开始采集数据
        collectData();
    }
}
//处理 天线停止扫描按钮 发出的点击信号
void MainWindow::on_pbtnStopSweep_clicked()
{
    char stopbuf[]={0x53,0x01,0x50,0x5C,0};
    serialPort.write(stopbuf,4);
}

void MainWindow::on_pbtnAzimuth_clicked()
{
    //方位定位
}

void MainWindow::on_pbtnElevation_clicked()
{
    //仰角定位
}
/*停止采集*/
void MainWindow::on_pbtnStop_clicked()
{
    if(true == rvp9.isWorking){
        rvp9.isWorking = false;
        ui->pbtnStop->setEnabled(false);
        ui->pbtnCollect->setEnabled(true);
        ui->comboBoxDPrf->setEnabled(true);
        ui->comboBoxPulseWidth->setEnabled(true);
        ui->comboBoxDopFilter->setEnabled(true);
        ui->comboBoxLmsk->setEnabled(true);
        ui->comboBoxDPrf->setEnabled(true);
    }
}

/*恢复采集*/
void MainWindow::on_pbtnCollect_clicked()
{
    if(false == rvp9.isWorking){
        rvp9.isWorking = true;
        ui->pbtnStop->setEnabled(true);
        ui->pbtnCollect->setEnabled(false);
        ui->comboBoxDPrf->setEnabled(false);
        ui->comboBoxPulseWidth->setEnabled(false);
        ui->comboBoxDopFilter->setEnabled(false);
        ui->comboBoxLmsk->setEnabled(false);
        ui->comboBoxDPrf->setEnabled(false);
    }
}

/*扫描方式  改变*/
void MainWindow::on_comboBoxMode_activated(int index)
{
    if(0 == index){
        //同步模式
        rvp9.procMode = procSyncModec;
        //不同扫描模式 下的天线扫描命令
        rvp9.antennaBuf[3] = 0xF1;
    }else if(1 == index){
        //free running模式
        rvp9.procMode = procFreeRunModec;
        rvp9.antennaBuf[3] = 0xF2;
        //时间序列模式
    }else if(2 == index){
        rvp9.procMode = procTimeSerisModec;
        rvp9.antennaBuf[3] = 0xF3;
    }
}
/*扫描距离 改变  距离掩码相关*/
void MainWindow::on_comboBoxLmsk_activated(int index)
{
    if(0 == index){
        rvp9.distance = disrange_10;
    }else if(1 == index){
        rvp9.distance = disrange_20;
    }else if(2 == index){
        rvp9.distance = disrange_30;
    }else if(3 == index){
        rvp9.distance = disrange_50;
    }else if(4 == index){
        rvp9.distance = disrange_150;
    }else if(5 == index){
        rvp9.distance = disrange_300;
    }
    //根据选择的距离 设置距离掩码
    rvp9.loadRangeMsk();
}
/*RPF 脉冲重复频率 改变*/
void MainWindow::on_comboBoxPRF_activated(int index)
{
    if(0 == index){
        rvp9.setpwfPRF = 300;
    }else if(1 == index){
        rvp9.setpwfPRF = 500;
    }else if(2 == index){
        rvp9.setpwfPRF = 1000;
    }else if(3 == index){
        rvp9.setpwfPRF = 2000;
    }else if(4 == index){
        rvp9.setpwfPRF = 3000;
    }else if(5 == index){
        rvp9.setpwfPRF = 4000;
    }else if(6 == index){
        rvp9.setpwfPRF = 5000;
    }
}
/*双脉冲重复比 改变   改变后仍需对PROC命令的8、9位进行设置*/
void MainWindow::on_comboBoxDPrf_activated(int index)
{
    if(0 == index){
        rvp9.procUnfold =procUnfoldNone;
    }else if(1 == index){
        rvp9.procUnfold =procUnfold2To3;
    }else if(2 == index){
        rvp9.procUnfold =procUnfold3To4;
    }else if(3 == index){
        rvp9.procUnfold =procUnfold4To5;
    }
}
/*脉宽  改变*/
void MainWindow::on_comboBoxPulseWidth_activated(int index)
{
    if(0 == index){
        rvp9.setpwfPulseWidth = 1;
    }else if(1 == index){
        rvp9.setpwfPulseWidth = 5;
    }else if(2 == index){
        rvp9.setpwfPulseWidth = 10;
    }else if(3 == index){
        rvp9.setpwfPulseWidth = 20;
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
    //rvp9.azimuth = arg1;
}
/*设置仰角角度*/
void MainWindow::on_doubleSpinBoxElevation_valueChanged(double arg1)
{
    //rvp9.elevation = arg1;
}
/*数据采集*/
int MainWindow::collectData(){
    rvp9.calculateVmax();
    rvp9.isWorking = true;
    fetchDataThread.start();
    while(rvp9.isWorking)
    {
        QApplication::processEvents();
        unsigned short azimuths,elevations;
        float azimuthf,elevationf;
        //4个字 8个字节 包含两个32位的TAG样本
        //拼装一个完整的相位
        azimuths=(((unsigned char)rvp9.outbuff[0]+(unsigned char)rvp9.outbuff[1]*256)>>4);
        azimuthf=float(azimuths)*360.0/4096.0;
        elevations=(((unsigned char)rvp9.outbuff[2]+(unsigned char)rvp9.outbuff[3]*256)>>4);
        elevationf=float(elevations)*360.0/4096.0;
        //将角度折叠到[-PI,PI]
        if(azimuthf>=180&&azimuthf<360)
            azimuthf=azimuthf-360;
        //更新相位控件的值
        ui->spinBoxAzimuthDisp->setValue(azimuthf);
        if(elevationf>=180&&elevationf<360)
        {
            elevationf=-(360-elevationf);
        }
        //更新仰角控件的值
        ui->spinBoxElevationDisp->setValue(elevationf);
    }
}

void MainWindow::closeEvent(QCloseEvent * closeEvent){
    switch( QMessageBox::information( this, tr("关闭应用程序"),
                                      tr("是否确定要关闭应用程序？"),
                                      tr("确定"), tr("取消"), 0, 1 ) )
    {
    case 0:
        if(rvp9.isWorking)
        {
            rvp9.isWorking = false;
            fetchDataThread.threadFlag = false;
            fetchDataThread->wait();
            delete fetchDataThread;
        }
        closeEvent->accept();
        break;
    case 1:
    default:
        closeEvent->ignore();
        break;
    }
}
