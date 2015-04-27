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
