#ifndef RVP900_H
#define RVP900_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <qstring.h>

//rvp900 控制类
#include "constRVP900.h"
#include "dispdevice.h"

#include "constcode.h"

extern DispDevice dispDev;
extern int dispMode;

class RVP900
{
    //RVP900 Properties
public :

    //距离库个数 与距离掩码设置位个数相同
    int binsNum;
    //采集数据种类 dBz,dBt,dBw,v，默认为ALL
    bool dataZDR_BIT,dataZ_BIT,dataT_BIT,dataV_BIT,dataW_BIT,dataALL,dataARC_BIT,dataKDP_BIT;
    int dataTypeNums;
    //采集的数据是否包含 头部TAG，默认为true
    bool noHeader;
    //采集数据的头信息
    bool hdrTag_BIT,hdrPRT_BIT,hdrPul_BIT,hdrTim_BIT,hdrGpm_BIT,
    hdrFlg_BIT,hdrUTC_BIT,hdrMMT_BIT,hdrSYT_BIT,hdrPBN_BIT,hdrTID_BIT;
    //数据头的长度 以字节计
    int hdrBytesNum,dataBytesNum ;
    //距离量程 distance range,目前仅设置六个距离范围
    enum enum_disRange
    {RANGE_FIRST=10,RANGE_SECOND=20,RANGE_THIRD=30,
        RANGE_FOURTH=50,RANGE_FIFTH=150,RANGE_SIXTH=300} disRange;
    //脉冲重复频率
    enum enum_PRF
    {PRF_FIRST=300,PRF_SECOND=500,PRF_THIRD=1000,
        PRF_FOURTH=2000,PRF_FIFTH=3000,PRF_SIXTH=4000,PRF_SEVENTH=5000} PRF;

    /*数据采集方式 collect mode,有三种Synchronous，
    *free running，time series，默认是time series
    */
    enum enum_colMode {SYNCHRONOUS,FREE_RUNNING,TIME_SERIES} colMode;
    //脉冲宽度 1us,5us,10us,20us,默认1us
    int pulseWidth;
    //双PRF，脉冲重复比,此处不是真实比率
    enum enum_PRF_Ratio{PRF_NONE,PRF_2TO3,PRF_3TO4,PRF_4TO5} PRF_Ratio;
    //多普勒滤波器 doppler filter
    enum enum_dopFilter {DF_NONE,DF_ONE,DF_TWO,DF_THREE,DF_FOUTH,
                         DF_FIVE,DF_SIX,DF_SEVEN} dopFilter;
    //处理模式 processing mode
    enum enum_proMode {PPP,FFT,RPP,DPRT_1,DPRT_2} proMode;
    //脉冲累积数 pulse accummunate
    enum enum_pulAccumulate {};
    //Threshold of LOG、SIG、CCOR、SQI,门限值
    float LOG_Threshold,SIG_Threshold,CCOR_Threshold,SQI_Threshold;
    //R2使能 r2 enable
    bool RTwoEnable;
    //距离平均 distance averaging
    unsigned char avgDistance;
    /*天线相位角 方位角 仰角*/
    double azimuth,elevation;
    //以下参数有待查阅
    /*杂项控制 1、距离订正通断 2、r2使能 3、单库杂波消除 4、强度斑点消除 5、速度斑点消除 6、3x3平滑输出**/

    //距离分辨率25-1000 米，默认125米，通过TTY设置
    int resolution;
    /*socket to RVP9*/
public:
    int  clientSocket;

    /*RVP900 buffer*/
public:
    char sendBuffer[1024*8];//发送指令buffer 用于缓存与指令相关信息
    char recvBuffer[1024*8];//接收数据buffer
    char dataOutBuff[1024*16];//接收数据buffer
    char formatuffer[10];
    unsigned char low8Bits,high8Bits;//一个双字的低位字buffer，和高位字buffer

    unsigned char inputNBuff;//指令输入参数缓冲区

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

    /*predefined parameter variable of command ，预定义的指令参数*/
public:
    unsigned char SOPRM[52]={
        0x98,0,0,0,0,0,0,0,0,0,0x2,0,0x20,0,0xa6,0x5,
        0xae,0x7,0x30,0,0x40,0xfe,0x5,0,0x22,0,0x92,
        0x0,0,0x1,0xa,0x2,0xaa,0xaa,0x88,0x88,0xa0,0xa0,
        0xa0,0xa0,0,0,0,0,0x40,0x6,0,0,0,0,0x80,0xc};
    unsigned char LDRNV[504]={0x15,0,0};

    /*RVP900 Methods*/
public:
    RVP900();
    ~RVP900();
    int connectRVP();//连接到server socket
    int openRVP900();//发送一组命令 打开RVP900
    int readSocketResp();//读取rvp900响应信息
    int assembleCmdMsg(int length,char *cmd,char *data);//构造要发送的命令的信息
    int sendMsg(char *buffer,int length);//向RVP900发送数据
    int getRvp900status(char *buffer);//获取RVP900的状态信息
    /*
    *构造发送的指令信息
    */
    int comboCmdMsg(char *cmd,char *data,int length);
    /*
    *Get Processor Parameters(GPARM),used to access status information from RVP900
    *获取RVP900的状态
    */
    int getProParameters();
    /*
    *reset ommand will reset entire rvp900,flags in cmmand determine the action to be taken
    * 重置指令会将rvp900全部重置，指令后总的标志位决定了会进行的操作
    */
    int reset();
    /*
    *IOTEST command used to Test Input and output data buses of signal processor interface
    * 该命令用来测试信号处理器接口的输入、输出数据总线是否OK
    */
    int IOTest();
    /*
    *The RVP900 can operate in a mode wherein radar data are acquired in
    *synchronization with the antenna motion along either the azimuth or
    *elevation axis
    *该命令用来加载天线的旋转的角度表 天线可以按照相位角、仰角的方式旋转
    */
    int loadSync();
    /*
    *setup opertating parameters, The command
    *should be issued whenever any of the parameters in the list change. The
    *default parameter list consists of twenty 16-bit input words
    *设置操作参数,当列表中 参数有改变时 则需执行该命令。默认的参数列表由20个16位输入字组成
    */
    int setOperPRM();
    /*
     *Configure Ray Header Words
    *The processed data that are output by the PROC command may contain
    optional header words that give additional information about each ray.
    This command configures the set of words that makeup each header. There
    are (up to) thirty two different choices of words or groups of words to
    include, as indicated by the bit mask following the command.
    PROC命令处理后的输出数据可能包含可选的头字数据，这些头字可以提供关于每条射线额外的信息
    该命令配置字集，这些字集组成每个头。一共有32个不同的字、字组选择，由命令后面的位掩码表示
    */
    int CFGHDR();
    /*
    *This command informs the signal processor of the ranges at which data are
    *to be collected. An arbitrary set of range bins are selected via an 8192-bit
    *mask.
    *该命令指示信号处理器在哪些位置收集数据。通过8192个掩码位来选择一个任意的距离库集合
    *距离库产生公式：RES*（N-1），N表示第N位，RES表示距离分辨率
    */
    int loadRanMsk(int ranMark);
    /*
    *LFILT:Load Clutter Filter Flags
    *A special feature of the RVP9 processor is that any of the available clutter
    *filters may be chosen independently at each selected range. This range-dependent
    *clutter removal is useful when the clutter characteristics vary
    *with increasing range.
    *载入杂波滤波器标志
    *RVP9处理器的一个特点是可以再每个选择的距离处使用不同的杂波滤波器。
    *该功能在滤除随距离变化的杂波时相当有用。
    */
    int setLFILT(char *buffer);
    /*
    *set pulse width and PRF
    *This command selects the pulse width and trigger rate. A 4-bit pulse width
    *code is passed in bits (13,12,9,8) of the command word, and selects one of
    *sixteen pulse widths as described under PWINFO.
    *设置脉冲宽度和脉冲重复频率
    *该命令用来选择脉冲宽度和触发频率。一个4位的脉冲宽度码在该命令字的（13，12,9,8）位设置，
    *正如PWINFO命令的描述，选择1/16的脉冲宽度
    */
    int setPulWidth(char *buffer);
    /*
    *SNOISE :sample noise level
    *This command is used to estimate the current noise level from the receiver,
    *so that the noise can be subtracted from subsequent measurements. Data
    *are sampled for 256 pulses at 256 bins, beginning at a selectable range and
    *spaced by the range resolution at that pulse width. The internal trigger
    *generator is temporarily set to a special noise rate (usually much lower than
    *the operating rate) during the process.
    *对噪声电平采样
    *该命令用来估计当前接收机的噪声大小，这样就可以从随后测量值中减去该噪声。256个脉冲在256个距离
    *处采样，在可选距离处开始，。。。
    */
    int samNoise();
    /*
    *PROC : initate processing command
    *The PROC command controls the actual processing and output of radar
    *data. PROC is a single-word command that specifies the type of processing to
    *be performed, and the type of output to be generated. The two mode bits in
    *the command word select either:
    *Synchronous mode————The processor acquires, processes, and outputs
    *one ray in response to each PROC command. Processing is begun
    *only after each command is actually received.
    *Free running mode————A single PROC command is issued, and rays
    *are continually output as fast as they can be produced and consumed.
    *This continues until any other command is written
    *Time Series mode————The processor acquires, processes, and outputs
    *one ray of time series samples in response to each PROC command.
    *Similar to Synchronous mode above. Data are output as 8-bit time
    *series, 16-bit time series, or 16-bit power spectra
    *PROC:开始处理指令
    *PROC指令控制实际的处理和雷达数据的输出。PROC指令是一个单字命令，该命令指定了进行处理的方式
    *和输出类型。命令中的两个模式位可以选择：
    *同步模式————每执行一次PROC命令，处理器获取处理、输出一个雷达射线。在接收到每个指令后，处理才开始。
    *自由运行模式————执行单个PROC指令，射线持续输出，其速度和射线产生、处理一样快。
    *该过程会持续进行下去，知道写入另外一个命令
    *时间序列模式————每执行一个PROC指令，处理器获取、长生输出一个射线的时间序列样本。
    *和上面的同步模式相似。数据以8位、16位时间序列或者16位功率谱的形式输出
    */
    int PROC(unsigned char *outBuffer);
    /*
    *GPARM : Get Processor Parameters
    *This command is used to access status information from the RVP900
    *processor. Sixty-four words are always transferred, some later words are
    *reserved for future compatibility and are read as zeros.
    *获取处理器参数
    *该命令用来访问RVP900处理器的状态信息。一般都传输64位字，出于将来兼容性考虑，
    *保留后面的字，作为0读出
    */
    int GPARM(char* inBuffer,char *outBuffer);
    /*RVP900初始化函数 对参数进行必要的初始化*/
    int RVP9Initialize();
    /*返回数据头的长度*/
    int getHeaderLength();
    /*计算返回的数据长度*/
    int getDataLength();
};

#endif // RVP900_H
