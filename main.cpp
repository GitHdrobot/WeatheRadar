#include "mainwindow.h"
#include <QApplication>

RVP900 rvp9;//rvp9控制对象

DispDevice dispDev;//存放显示设备信息

int dispMode;

unsigned char paintBuff[1024];//绘图数据缓冲区

unsigned char outbuff[1024*16];//读取数据缓冲区

unsigned char binsZBuff[1024];//dbZ bins buff

unsigned char binsWBuff[1024];//W bins buff

unsigned char binsVBuff[1024];//V bins buff

unsigned char binsTBuff[1024];//dBT bins buff

//暂不需要这些数据
/*
unsigned char binsZDRBuff[1024];//ZDR bins buff
unsigned char binsKDPBuff[1024];//KDP bins buff
unsigned char binsKDPBuff[1024*6];//ARC bins buff
*/
unsigned char binsTAGBuff[8];//TAG buff

/*
*For a radar of wavelength λ operating at a fixed sampling period τs =
*1/PRF, the unambiguous velocity and range intervals are given by:
*Vu = λ /(4*τs) and Ru = τs * c / 2
*对于一个波长为λ，固定采样周期τs = 1/PRF，不模糊速度和不模糊范围由下式计算
*
*/
float VUnam = 2.4;//最大不模糊速度 velocity unambiguous

/*
*An important feature of the RVP900 is its ability to eliminate signals which
*are either too weak to be useful, or which have widths too large to justify
*further analysis. This is done through SQI, which is defined as:
*SQI = |R1| / R0
*RVP900 的一个重要特性是，它可以消除那些太弱而不能使用的信号，或者那些谱宽太大不能作进一步分析的信号
*这是通过SQI完成的，SQI的等式如下：
*SQI的高斯模型
*
*SQI = (SNR / (SNR+1)) * (e^(-PI^2 * W^2) / 2)
*当SNR很大时 ，SQI是谱宽W的函数，当谱宽 W = 0 时，SQI是信噪比SNR的函数
*/
float SQI = 0.4;//signal quality index，信号质量指标

//线程标识
bool ThreadFlag=false;

//脉冲重复频率
int PRF=300;
//脉冲重复频率比
int PRFRatio=0;
//pulseWIdth表示脉宽，默认1us 1*10^-3*3*10^8
int pulseWidth = 1;
//扫描方式
int sweepMode = 2;
//距离量程
int distance = 10;
//天线扫描串口命令
char Abuf[7]={0x53,0x04,0x53,0xF2,0x00,0x00,0x00};



unsigned char SaveBuffer1[32][968]={0x0}; //扫描方式一的数据保存数组
unsigned char SaveBuffer2[62][968]={0x0};//扫描方式二的数据保存数组
unsigned char SaveBuffer3[122][968]={0x0};//扫描方式三的数据保存数组
unsigned char echo_data[980][650]={0x0}; //绘图区域对应的回波数据存放数组
//RVP参数配置信息
/*unsigned char SOPRM[52]={0x98,0,0,0,0,0,0,0,0,0,0x2,0,0x20,0,0xa6,0x5,0xae,0x7,0x30,0,0x40,0xfe,
                     0x5,0,0x22,0,0x92,0x0,0,0x1,0xa,0x2,
                     0xaa,0xaa,0x88,0x88,0xa0,0xa0,0xa0,0xa0,0,0,0,0,0x40,0x6,0,0,0,0,0x80,0xc};
*/
//RVP900主机名
const char *rvp900_hostname="RVP900";
//RVP900通信端口号
int rvp900port=30740;
//socket handle
int clientsocket;
//数据发送buffer
char sSendBuffer[1024*32];
//数据接收buffer
char sRecvBuffer[1024*32];
//距离订正表
unsigned char LDRNV[504]={0x15,0,0};
//脉冲比
char PulseRatio=0x80;

int P,serial_fd;
/*M是判断是否采集回波数据的标志；
 *PRF1设置脉冲重复频率；
 *PRF_Ratio表示脉冲重复比；
 *sebiao_v是不同PRF在显示速度色标的标志；
 *PULSE_MARK表示脉宽，默认1us
 */
int M=0,PRF1=300,PRF_Ratio=0,sebiao_v=0,PULSE_MARK=1;
/*S表示扫描方式，默认方式2；
 *Sum；
 *Range_Mark距离量程
*/
int S=2,Sum=5,Range_Mark=10;
float factor=2.4,sqi=0.4;//factor表示最大不模糊速度；
float factor2=10.0; //factor2表示距离，用于游标显示计算回波具体信息
long int total=60016;
unsigned int num=0,i_time=0;
int year1=0,year2=0,month=0,day=0,hour=0,minute=0,second=0;
float Set[40]={0.0};
bool AngleMark=true;
bool BufferMark;//=true;
char Abuf[7]={0x53,0x04,0x53,0xF2,0x00,0x00,0x00}; //天线扫描串口命令
unsigned char buffer[128]={0x0};                                                  //
unsigned char rBuffer[16000]={0x0};
unsigned char cBuffer[121][968]={0x0}; //同时绘制4幅图时，半径240，存放数据的数组
unsigned char cBuffer1[121][1208]={0x0};
unsigned char cBuffer2[121][2008]={0x0};
unsigned char pBuffer[968]={0x00};
unsigned char PW_Buffer[3]={0x0}; //脉宽和脉冲重复频率设置
unsigned char lrmsk[2]={0x01,0x01}; //扫描距离设置
unsigned char lfilt[2]={0x00,0x00}; //滤波器设置
unsigned char ratio[2]={0x80,0x00}; //脉冲重复比设置
unsigned char elBuffer[2]={0x00,0x00};

/*初始化函数**/
int initialize();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

int initialize(){
    //打开一个设置文件，读取设置信息
}
