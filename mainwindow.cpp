#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rvp900.h"



extern RVP900 rvp9;//rvp9控制对象


QRect timeRect,dateRect,freqRect,eleRect,dfreqRatioRect,distanceRect;//save rect of time,date,frequency,elevation

//扇形半径
int sectorWidth ,colorTotal;

//disp mode
unsigned short dispMode;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    //slot signal connect
    slotSignalconnect();
    //display info initialize
    dispInitiallize();

    getDispInfo();
    //serial port initialze
    serialPortInitilize();
    //int serial_fd=PortOpen(&portinfo);
    //if(serial_fd<0){printf("serial open failed!!!");}else{
    //    QTimer *timer = new QTimer(this);
    //    connect(timer,SIGNAL(timeout()),this,SLOT(send_Slot()));
    //    timer->start(1000);}
    //    PortSet(serial_fd,&portinfo);
    //rvp900 initialize
    rvp9.RVP9Initialize();
    //connect to RVP900
    rvp9.connectRVP9();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete &rvp9;
}
void MainWindow::serialPortInitilize(){
    /*对串口进行设置*/
    serialPort.setPortName(TTY_DEV4);
    serialPort.setBaudRate(BAUD38400);
    serialPort.setFlowControl(FLOW_XONXOFF);
    serialPort.setParity(PAR_NONE);
    serialPort.setDataBits(DATA_8);
    serialPort.setStopBits(STOP_1);
}
void MainWindow::dispInitiallize(){
    /*获取显示设备可用的分辨率*/
    QDesktopWidget *dwsktopwidget = QApplication::desktop();
    QRect deskrect = dwsktopwidget->availableGeometry();
    //QRect screenrect = dwsktopwidget->screenGeometry();
    dispDev.setWidth(deskrect.width());
    dispDev.setHeight(deskrect.height());
    this->resize(dispDev.width,dispDev.height);
    QPoint wCenter(deskrect.width()/8,deskrect.height()/8);
    this->move(wCenter);
    /*
        this->setMaximumHeight(dispDev.height);
        this->setMaximumWidth(dispDev.width);
        this->setMinimumHeight(dispDev.height);
        this->setMinimumWidth(dispDev.width);
    */
    //defalut display 4 pic mode
    dispMode = disp4PicMode;
    ui->pbtnCloseTransmit->setEnabled(false);
    ui->pbtnStop->setEnabled(false);
    ui->pbtnStopSweep->setEnabled(false);
    //load pix
    pix_red.load(":/res/res/red_24.ico");
    pix_green.load(":/res/res/green_24.ico");

}


void MainWindow::slotSignalconnect(){
    connect(ui->actionParaSetting,SIGNAL(triggered()),this,SLOT(paraSetSlot()));
    connect(ui->actionSample,SIGNAL(triggered()),this,SLOT(sampleSlot()));

    connect(ui->action4_Pic,SIGNAL(triggered()),this,SLOT(dispFourPicSlot()));
    connect(ui->action2_dbzw,SIGNAL(triggered()),this,SLOT(disp2PicZWSlot()));
    connect(ui->action2_dbzv,SIGNAL(triggered()),this,SLOT(disp2PicZVSlot()));
    connect(ui->action2_dbzt,SIGNAL(triggered()),this,SLOT(disp2PicZTSlot()));
    connect(ui->action2_dbtw,SIGNAL(triggered()),this,SLOT(disp2PicTWSlot()));
    connect(ui->action2_dbtv,SIGNAL(triggered()),this,SLOT(disp2PicTVSlot()));
    connect(ui->action2_vw,SIGNAL(triggered()),this,SLOT(disp2PicVWSlot()));

    connect(ui->action1_dbz,SIGNAL(triggered()),this,SLOT(disp1PicZSlot()));
    connect(ui->action1_dbt,SIGNAL(triggered()),this,SLOT(disp1PicTSlot()));
    connect(ui->action1_v,SIGNAL(triggered()),this,SLOT(disp1PicVSlot()));
    connect(ui->action1_w,SIGNAL(triggered()),this,SLOT(disp1PicWSlot()));

    connect(ui->spinBoxAzimuthSet,SIGNAL(valueChanged(int)),SLOT(on_doubleSpinBoxAzimuth_valueChanged(int)));
    connect(ui->spinBoxElevationSet,SIGNAL(valueChanged(int)),SLOT(on_doubleSpinBoxElevation_valueChanged(int)));
    connect(ui->pbtnOpenTransmit,SIGNAL(clicked()),SLOT(on_pbtnOpenTransmit_clicked()));
    connect(ui->pbtnCloseTransmit,SIGNAL(clicked()),SLOT(on_pbtnCloseTransmit_clicked()));
    connect(ui->pbtnSweep,SIGNAL(clicked()),SLOT(on_pbtnSweep_clicked()));
    connect(ui->pbtnStopSweep,SIGNAL(clicked()),SLOT(on_pbtnStopSweep_clicked()));
    connect(ui->pbtnAzimuth,SIGNAL(clicked()),SLOT(on_pbtnAzimuth_clicked()));
    connect(ui->pbtnElevation,SIGNAL(clicked()),SLOT(on_pbtnElevation_clicked()) );
    connect(ui->pbtnStop,SIGNAL(clicked()),SLOT(on_pbtnStop_clicked()),Qt::QueuedConnection );
    connect(ui->pbtnCollect,SIGNAL(clicked()),SLOT(on_pbtnCollect_clicked()));
    connect(ui->comboBoxMode,SIGNAL(activated(int)),SLOT(on_comboBoxMode_activated(int)));
    connect(ui->comboBoxLmsk,SIGNAL(activated(int)),SLOT(on_comboBoxLmsk_activated(int)));
    connect(ui->comboBoxPRF,SIGNAL(activated(int)),SLOT(on_comboBoxPRF_activated(int)));
    connect(ui->comboBoxDPrf,SIGNAL(activated(int)),SLOT(on_comboBoxDPrf_activated(int)));
    connect(ui->comboBoxPulseWidth,SIGNAL(activated(int)),SLOT(on_comboBoxPulseWidth_activated(int)));
    connect(ui->comboBoxDopFilter,SIGNAL(activated(int)),SLOT(on_comboBoxDopFilter_activated(int)));


    connect(ui->action2_dbzw,SIGNAL(triggered()),this,SLOT(disp2PicZWSlot()));
    connect(ui->action2_dbzv,SIGNAL(triggered()),this,SLOT(disp2PicZVSlot()));
    connect(ui->action2_dbzt,SIGNAL(triggered()),this,SLOT(disp2PicZTSlot()));
    connect(ui->action2_dbtw,SIGNAL(triggered()),this,SLOT(disp2PicTWSlot()));
    connect(ui->action2_dbtv,SIGNAL(triggered()),this,SLOT(disp2PicTVSlot()));
    connect(ui->action2_vw,SIGNAL(triggered()),this,SLOT(disp2PicVWSlot()));

    connect(ui->action1_dbz,SIGNAL(triggered()),this,SLOT(disp1PicZSlot()));
    connect(ui->action1_dbt,SIGNAL(triggered()),this,SLOT(disp1PicTSlot()));
    connect(ui->action1_v,SIGNAL(triggered()),this,SLOT(disp1PicVSlot()));
    connect(ui->action1_w,SIGNAL(triggered()),this,SLOT(disp1PicWSlot()));

}
void MainWindow::paraSetSlot()
{
    //qDebug( "my icon size = %x", this->iconSize() );
    DialogSetting *dlgSetUi = new DialogSetting();
    dlgSetUi->setFocus();
    dlgSetUi->setModal(true);
    dlgSetUi->show();
}

void MainWindow::sampleSlot()
{
    //qDebug( "my icon size = %x", this->iconSize() );
    DialogSample *pDlgSampleUi = new DialogSample();
    pDlgSampleUi->setFocus();
    pDlgSampleUi->setModal(true);
    pDlgSampleUi->show();
}

//处理 打开发射按钮 发出的点击信号
void MainWindow::on_pbtnOpenTransmit_clicked()
{
    if(ui->pbtnOpenTransmit->isEnabled()){
        char openbuf[]={0x54,0x01,0xAA,0x01,0};
        serialPort.write(openbuf);
        serialPort.read(rvp9.rcverStatus,8);
        //改变相关显示状态
        ui->pbtnOpenTransmit->setEnabled(false);
        ui->pbtnCloseTransmit->setEnabled(true);
        //change pic
       rvp9StateDisp(rvp9.rcverStatus);
    }

}
//处理 关闭发射按钮 发出的点击信号
void MainWindow::on_pbtnCloseTransmit_clicked()
{
    if(ui->pbtnCloseTransmit->isEnabled()){
        char closebuf[]={0x54,0x01,0x55,0x56,0};
        serialPort.write(closebuf);
        serialPort.read(rvp9.rcverStatus,8);
        //改变相关显示状态
        ui->pbtnCloseTransmit->setEnabled(false);
        ui->pbtnOpenTransmit->setEnabled(true);
        //change pic
       rvp9StateDisp(rvp9.rcverStatus);
    }

}
//处理 天线扫描按钮 发出的点击信号
void MainWindow::on_pbtnSweep_clicked()
{
    //使 停止扫描按钮 使能
    ui->pbtnStopSweep->setEnabled(true);
    ui->pbtnSweep->setEnabled(false);

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
    rvp9.isWorking = true;
    //    ui->pbtnCollect->setEnabled(false);
    //    ui->pbtnStop->setEnabled(true);

}
//处理 天线停止扫描按钮 发出的点击信号
void MainWindow::on_pbtnStopSweep_clicked()
{
    if(ui->pbtnStopSweep->isEnabled()){
        char stopbuf[]={0x53,0x01,0x50,0x5C,0};
        serialPort.write(stopbuf,4);
        ui->pbtnStopSweep->setEnabled(false);
        ui->pbtnSweep->setEnabled(true);
    }
    //    if(rvp9.isWorking == true){
    //        ui->pbtnCollect->setEnabled(false);
    //        ui->pbtnStop->setEnabled(true);
    //    }else{
    //        ui->pbtnCollect->setEnabled(true);
    //        ui->pbtnStop->setEnabled(false);
    //    }

}
//方位定位
void MainWindow::on_pbtnAzimuth_clicked()
{
    char azimuthBuf[6]={0x53,0x03,0x41,0x00,0x00,0x00};
    char ch_t;
    float azimuth,azimuth_t;
    int azimuthi;
    azimuth_t=ui->spinBoxAzimuthSet->value();
    if (azimuth_t>=0&&azimuth_t<=60)
        azimuth=azimuth_t*4096.0/360.0;
    else if(azimuth_t>=-60&&azimuth_t<0)
        azimuth=(360+azimuth_t)*4096.0/360.0;
    azimuthi=azimuth;
    azimuthBuf[3]=azimuthi%256;
    azimuthBuf[4]=azimuthi/256;
    ch_t=azimuthBuf[0]+azimuthBuf[1]+azimuthBuf[2]+azimuthBuf[3]+azimuthBuf[4];
    azimuthBuf[5]=0-ch_t;
    serialPort.write(azimuthBuf,6);
}
//仰角定位
void MainWindow::on_pbtnElevation_clicked()
{

    char elevationBuf[6]={0x53,0x03,0x45,0x00,0x00,0x00};
    char ch_t;
    float elevation,elevation_t;
    int elevationi;
    elevation_t=ui->spinBoxAzimuthSet->value();
    if (elevation_t>=0&&elevation_t<=60)
        elevation=elevation_t*4096.0/360.0;
    else if(elevation_t>=-60&&elevation_t<0)
        elevation=(360+elevation_t)*4096.0/360.0;
    elevationi=elevation;
    elevationBuf[3]=elevationi%256;
    elevationBuf[4]=elevationi/256;
    ch_t=elevationBuf[0]+elevationBuf[1]+elevationBuf[2]+elevationBuf[3]+elevationBuf[4];
    elevationBuf[5]=0-ch_t;
    serialPort.write(elevationBuf,6);
}
/*停止采集*/
void MainWindow::on_pbtnStop_clicked()
{
    //    if(true == ui->pbtnStop->isEnabled()){
    if(true == rvp9.isWorking){
        rvp9.isWorking = false;
        ui->pbtnStop->setEnabled(false);
        ui->pbtnCollect->setEnabled(true);
        ui->comboBoxDPrf->setEnabled(true);
        ui->comboBoxPulseWidth->setEnabled(true);
        ui->comboBoxDopFilter->setEnabled(true);
        ui->comboBoxLmsk->setEnabled(true);
        ui->comboBoxDPrf->setEnabled(true);
        //ui->pbtnSweep->setEnabled(false);
        //ui->pbtnOpenTransmit->setEnabled(false);
    }
}

/*开始采集*/
void MainWindow::on_pbtnCollect_clicked()
{
    //if(true == ui->pbtnCollect->isEnabled()){
    if(false == rvp9.isWorking ){
        rvp9.isWorking = true;
        ui->pbtnStop->setEnabled(true);
        ui->pbtnCollect->setEnabled(false);
        ui->comboBoxDPrf->setEnabled(false);
        ui->comboBoxPulseWidth->setEnabled(false);
        ui->comboBoxDopFilter->setEnabled(false);
        ui->comboBoxLmsk->setEnabled(false);
        ui->comboBoxDPrf->setEnabled(false);
        //ui->pbtnSweep->setEnabled(false);
        //ui->pbtnOpenTransmit->setEnabled(false);
        rvp9.setPwPrf();
        rvp9.setLFILT();
        //开始采集数据
        collectData();

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
        rvp9.pulsePRF = 300;
        rvp9.pulsePRT[0] = 0x1f;
        rvp9.pulsePRT[1] = 0x4e;
    }else if(1 == index){
        rvp9.pulsePRF = 500;
        rvp9.pulsePRT[0] = 0xdf;
        rvp9.pulsePRT[1] = 0x2e;
    }else if(2 == index){
        rvp9.pulsePRF = 1000;
        rvp9.pulsePRT[0] = 0x6f;
        rvp9.pulsePRT[1] = 0x17;
    }else if(3 == index){
        rvp9.pulsePRF = 2000;
        rvp9.pulsePRT[0] = 0xb7;
        rvp9.pulsePRT[1] = 0x0b;
    }else if(4 == index){
        rvp9.pulsePRF = 3000;
        rvp9.pulsePRT[0] = 0xcf;
        rvp9.pulsePRT[1] = 0x07;
    }else if(5 == index){
        rvp9.pulsePRF = 4000;
        rvp9.pulsePRT[0] = 0xdb;
        rvp9.pulsePRT[1] = 0x05;
    }else if(6 == index){
        rvp9.pulsePRF = 5000;
        rvp9.pulsePRT[0] = 0xaf;
        rvp9.pulsePRT[1] = 0x04;
    }

    rvp9.setPwPrf();
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
    switch(int(index))
    {
    case 0:  rvp9.dopFilter=0x00;  break;
    case 1:  rvp9.dopFilter=0x01;  break;
    case 2:  rvp9.dopFilter=0x02;  break;
    case 3:  rvp9.dopFilter=0x03;  break;
    case 4:  rvp9.dopFilter=0x04;  break;
    case 5:  rvp9.dopFilter=0x05;  break;
    case 6:  rvp9.dopFilter=0x06;  break;
    case 7:  rvp9.dopFilter=0x07;  break;
    default:break;
    }
}
/*设置方位角角度*/
void MainWindow::on_doubleSpinBoxAzimuth_valueChanged(int arg1)
{
    //rvp9.azimuth = arg1;
}
/*设置仰角角度*/
void MainWindow::on_doubleSpinBoxElevation_valueChanged(int arg1)
{
    //rvp9.elevation = arg1;
}
/*数据采集*/
int MainWindow::collectData(){
    rvp9.calculateVmax();
    //    rvp9.isWorking = true;
    fetchDataThread.threadFlag = true;
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


void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        event->accept();  //接受退出信号，程序退出
    }
}
int MainWindow::getDispInfo(){
    //save rect of time,date,frequency,elevation
    timeRect = ui->labelTime->geometry();
    dateRect = ui->labelDate->geometry();
    freqRect = ui->labelPRF->geometry();
    eleRect = ui->labelAntaElevation->geometry();
    dfreqRatioRect=ui->labelDPRF->geometry();
    distanceRect = ui->labelRange->geometry();
}

void MainWindow::errDialog(int errCode){
    QErrorMessage errMsgBox;
    errMsgBox.showMessage("running error ,error code is" + QString::number(errCode));
}


void  MainWindow::dispFourPicSlot(){//显示四图槽函数 ZTVW
    dispMode = disp4PicMode;
}
void  MainWindow::disp2PicZTSlot(){//显示2图槽函数 ZT
    dispMode = disp2PicZTMode;
}
void  MainWindow::disp2PicZVSlot(){//显示2图槽函数 ZV
    dispMode = disp2PicZVMode;
}
void  MainWindow::disp2PicZWSlot(){//显示2图槽函数 ZW
    dispMode = disp2PicZWMode;
    this->update();
}
void  MainWindow::disp2PicTVSlot(){//显示2图槽函数 TV
    dispMode = disp2PicTVMode;
    this->update();
}
void  MainWindow::disp2PicTWSlot(){//显示2图槽函数 TW
    dispMode = disp2PicTWMode;
    this->update();
}
void  MainWindow::disp2PicVWSlot(){//显示2图槽函数 VW
    dispMode = disp2PicVWMode;
    this->update();
}
void  MainWindow::disp1PicZSlot(){//显示1图槽函数 Z
    dispMode = disp1PicZMode;
    this->update();
}
void  MainWindow::disp1PicTSlot(){//显示1图槽函数 T
    dispMode = disp1PicTMode;
    this->update();
}
void  MainWindow::disp1PicVSlot(){//显示1图槽函数 V
    dispMode = disp1PicVMode;
    this->update();
}
void  MainWindow::disp1PicWSlot(){//显示1图槽函数 W
    dispMode = disp1PicWMode;
    this->update();
}

void MainWindow::rvp9StateDisp(char Rbuf[]){
    //发射状态
    if(Rbuf[1]&128)//发射通讯
        ui->label_tc->setPixmap(pix_green);
    else
        ui->label_tc->setPixmap(pix_red);

    if(Rbuf[1]&64)//电源
        ui->label_pwr->setPixmap(pix_green);
    else
        ui->label_pwr->setPixmap(pix_red);

    if(Rbuf[1]&32)//+28V
        ui->label_28Vol->setPixmap(pix_green);
    else
        ui->label_28Vol->setPixmap(pix_red);

    if(Rbuf[1]&16)//保护脉冲
        ui->label_pp->setPixmap(pix_green);
    else
        ui->label_pp->setPixmap(pix_red);

    if(Rbuf[1]&8)//过温
        ui->label_ht->setPixmap(pix_green);
    else
        ui->label_ht->setPixmap(pix_red);

    if(Rbuf[1]&4)//功率
        ui->label_walt->setPixmap(pix_green);
    else
         ui->label_walt->setPixmap(pix_red);

    if(Rbuf[1]&2)//发射
         ui->label_t->setPixmap(pix_green);
    else
        ui->label_t->setPixmap(pix_red);

    if(Rbuf[1]&1)//准加
        ui->label_add->setPixmap(pix_green);
    else
        ui->label_add->setPixmap(pix_red);

    //接收状态
    if(Rbuf[2]&8)//激励源
        ui->label_ds->setPixmap(pix_green);
    else
        ui->label_ds->setPixmap(pix_red);

    if(Rbuf[2]&4)//本振源
        ui->label_co->setPixmap(pix_green);
    else
        ui->label_co->setPixmap(pix_red);

    if(Rbuf[2]&2)//时钟源
        ui->label_clk->setPixmap(pix_green);
    else
        ui->label_clk->setPixmap(pix_red);

    if(Rbuf[2]&1)//相参基准
        ui->label_pb->setPixmap(pix_green);
    else
        ui->label_pb->setPixmap(pix_red);

    //伺服状态
    if(Rbuf[5]&128)//伺服通讯
        ui->label_servo->setPixmap(pix_green);
    else
        ui->label_servo->setPixmap(pix_red);
}
//void MainWindow::send_Slot()
//{
//    char Zbuf[]={0x3F,0x01,0x53,0x6D,0};
//    PortSend_1(serial_fd,Zbuf,4);
//    receive_Slot();
//}

//void MainWindow::receive_Slot()
//{
//    char Rbuf[8]={0,0,0,0,0,0,0,0};
//    //Rbuf[1]=0xaa;
//    PortRecv(serial_fd,Rbuf,8,38400);
//    //发射状态
//    if(Rbuf[1]&128)
//        pix1 = pix_green;
//    else
//        pix1 = pix_red;

//    if(Rbuf[1]&64)
//        pix2 = pix_green;
//    else
//        pix2 = pix_red;

//    if(Rbuf[1]&32)
//        pix3 = pix_green;
//    else
//        pix3 = pix_red;

//    if(Rbuf[1]&16)
//        pix4 = pix_green;
//    else
//        pix4 = pix_red;

//    if(Rbuf[1]&8)
//        pix5 = pix_green;
//    else
//        pix5 = pix_red;

//    if(Rbuf[1]&4)
//        pix6 = pix_green;
//    else
//        pix6 = pix_red;

//    if(Rbuf[1]&2)
//        pix7 = pix_green;
//    else
//        pix7 = pix_red;

//    if(Rbuf[1]&1)
//        pix8 = pix_green;
//    else
//        pix8 = pix_red;

//    //接收状态
//    if(Rbuf[2]&8)
//        pix9 = pix_green;
//    else
//        pix9 = pix_red;

//    if(Rbuf[2]&4)
//        pix10 = pix_green;
//    else
//        pix10 = pix_red;

//    if(Rbuf[2]&2)
//        pix11 = pix_green;
//    else
//        pix11 = pix_red;

//    if(Rbuf[2]&1)
//        pix12 = pix_green;
//    else
//        pix12 = pix_red;

//    //伺服状态
//    if(Rbuf[5]&128)
//        pix13 = pix_green;
//    else
//        pix13 = pix_red;

//}


