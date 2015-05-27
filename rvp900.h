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

    //PROC命令   标志位
    /*input#1 |ARC| Z | T | V | W |ZDR|Unfold |KDP
    *XARG#1 |HCL|FLG|Phi Rho Ldr|Phi Rho Ldr|SQI|RHV|PDP|
    *采集数据种类 dBz,dBt,dBw,v……
    * 该命令有三种模式，不同模式参数不同
    */
    /*同步多普勒、自由运行多普勒模式的输入参数缓冲区7-15  9bit,xarg 0-10bit*/
    bool procArc,procZ,procT,procV,procW,procKDP,procZDR;
    /*procUnfold
    *00 : No Unfolding 01 : Ratio of 2:3
    *10 : Ratio of 3:4 11: Ratio of 4:5
    * procTSOUT
    * Selects type of data to be output
    * 00 : 8-bit Time Series 01 : Power Spectrum
    * 10 : 16-bit Time Series 11 : Unused
    * 数据采集方式 collect mode,有三种Synchronous(01)，
    * free running(10)，time series(11)，默认是Synchronous
    */
    unsigned char procMode,procUnfold,procTSOUT,procTSSubType;
    /*通过XARG命令设置的参数*/
    //bool procXarg_HCL,procXarg_FLG,procXarg_Phi,procXarg_Rho,procXarg_Ldr;
    //bool procXarg_Phi,procXarg_Rho,procXarg_Ldr,procXarg_SQI,procXarg_RHV,procXarg_PDP;


    //SOPRM参数配置命令 input1-20,XARG1-9，7、8共用,
    //该命令参数太多 只添加几个常用到的参数变量
    //soprm参数初始化设置
    unsigned char soprm[52] = {
        0x98,0,0,0,0,0,0,0,0,0,//XARG指令操作码即4个可选参数1
        0x2,0,//soprm指令操作码
        0x20,0,0xa6,0x5,0xae,0x7,0x30,0,0x40,0xfe,// input#1 - input#20
        0x5,0,0x22,0,0x92,0x0,0,0x1,0xa,0x2,
        0xaa,0xaa,0x88,0x88,0xa0,0xa0,0xa0,0xa0,0,0,
        0,0,0x40,0x6,0,0,0,0,0x80,0xc
    };
    /*Nth,No Threshold；
    If 1, then no threshold values are set. This means ignore input words
    4, 5, 6, 7, 11, 12, 13, 14, and 18
    */
    bool soprmNth;
    //    /*input#1 The sample size is continually adjustable from 1 to 256 pulses*/
    //    unsigned short soprmSampleSize;
    //    /*input#2|ZNS| Polar |NHD|ASZ|16B|CMS| R2| |3x3|CCB| |Lsr|Dsr|Rnv|*/
    //    bool soprmZNS;
    //    unsigned char soprmPolar;
    //    bool soprmNHD,soprmASZ,soprm16B,soprmCMS,soprmR2,soprm3x3,soprmCCB,soprmLsr,soprmRnv;
    //    /*input#3-9 */
    //    unsigned short soprmLSB,soprmLOGTh,soprmCCOR,soprmSQITh,soprmSIG,soprmClbrtnReflcty,soprmTopMode;
    //    /*input #10 */
    //    bool soprmUVD,soprmPCT;
    //    unsigned char soprmWindow;
    //    bool soprmZER;
    //    unsigned char soprmcFtrStbDelay;


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
    float soprmSQI = 0.4;//signal quality index，信号质量指标
    //R2使能 r2 enable
    bool soprmR2Enable;
    //脉冲累积数 pulse accummunate
    unsigned short soprmPulseAcc;
    //Threshold of LOG、SIG、CCOR、SQI,门限值
    float soprmLOGThr,soprmSIGThr,soprmCCORThr,soprmSQIThr;
    //采集的数据是否包含 头部TAG，默认为false
    bool soprmNHD;
    //处理模式 processing mode
    unsigned short soprmProcessMode;

    //暂未使用
    //  unsigned char LDRNV[504]={0x15,0,0};



    //LRMSK  载入距离掩码  设置在哪写距离采集数据
    /*距离库的个数与设置的位和距离平均有关 binN = bitN/(avg+1)  */
    int lrmskBinsNum;
    //距离平均 distance averaging
    unsigned char lrmskRangeAvg;
    //距离量程 与设置的距离分辨率 距离掩码有关 distance = Res * (Nth - 1),默认10km
    int distance = 10;



    //CFGHDR
    /*|TID|PBN|SYT|MMT|UTC|Flg|Gpm|Tim|Pul|PRT|Tag|
    采集数据的头信息*/
    bool cfghdrTID,cfghdrPBN,cfghdrSYT,cfghdrMMT,cfghdrUTC,
    cfghdrFlg,cfghdrGpm,cfghdrTim,cfghdrPul,cfghdrPRT,cfghdrTag;


    //SETPWF  设置脉冲宽度和触发速度
    //脉冲重复频率
    int setpwfPRF=300;
    /*pulseWIdth表示脉宽，默认1us 1*10^-3*3*10^8,
     *脉冲宽度 1us,5us,10us,20us
     */
    int setpwfPulseWidth = 1;


    //LFILT Load Clutter Filter Flags
    //多普勒滤波器 doppler filter
    unsigned  short dopFilter;



    /*
    *For a radar of wavelength λ operating at a fixed sampling period τs =
    *1/PRF, the unambiguous velocity and range intervals are given by:
    *Vu = λ /(4*τs) and Ru = τs * c / 2
    *对于一个波长为λ，固定采样周期τs = 1/PRF，不模糊速度和不模糊范围由下式计算
    *
    */
    /*最大不模糊速度velocity unambiguous,雷达射频波长*/
    float Vmax ,waveLen ;


    //线程标识
    bool ThreadFlag=false;



    //数据头、数据的长度 以字节计
    int hdrBytesNum,dataBytesNum ;




    /*天线相位角 方位角 仰角*/
    double azimuth,elevation;

    //距离分辨率25-1000 米，默认125米，通过TTY设置
    int resolution;
    /*发射机发射、接收、伺服状态*/
    char rcverStatus[8];
    /*RVP900的工作状态*/
    bool isWorking;

    /*天线扫描的串口命令 该命令组成可能是：前三个字节，控制天线的开关；
     *第四个字节为扫描模式；第五六字节为角度信息；第七个字节不知（校验？）
    */
    char antennaBuf[7]={0x53,0x04,0x53,0xF2,0x00,0x00,0x00};
    /*天线仰角buffer 两个字节 一个字*/
    unsigned char elevationBuff[2]={0x00,0x00};

    /*雷达射频频率(工作频率) 频率与波长的关系式：c=λf*/
    int radioFrequency;

    /*socket to RVP9*/
    int  clientSocket;

    //以下参数有待查阅
    /*杂项控制 1、距离订正通断 2、r2使能 3、单库杂波消除 4、强度斑点消除 5、速度斑点消除 6、3x3平滑输出**/






    /*RVP900 buffer  相关缓冲区*/
public:
    char sendBuffer[1024*8];//发送指令buffer 用于缓存等待发送的指令相关信息

    char recvBuffer[1024*8];//用于缓存指令执行后返回的结果信息buffer

    char formatBuffer[10];//用于存放 将其他类型的数据格式化为字符（字节）的buffer

    unsigned char low8Bits,high8Bits;//一个双字节的低位字节buffer，和高位字节buffer

    unsigned char inputNBuff;//指令输入参数缓冲区

    unsigned char outbuff[1024*16];//存放执行PROC指令后 读取到的数据

    unsigned char binsZBuff[1024];//dbZ bins buff
    unsigned char binsWBuff[1024];//W bins buff
    unsigned char binsVBuff[1024];//V bins buff
    unsigned char binsTBuff[1024];//dBT bins buff
    unsigned char binsTAGBuff[1024];//TAG Buff 存放指令PROC执行后的tag数据

    //暂不需要这些数据
    /*
    unsigned char binsZDRBuff[1024];//ZDR bins buff
    unsigned char binsKDPBuff[1024];//KDP bins buff
    unsigned char binsKDPBuff[1024*6];//ARC bins buff
    */



    /*RVP900 Methods   方法*/
public:
    RVP900();
    ~RVP900();
    int iniCommand();//对命令进行必要的初始化
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
    int loadRangeMsk();
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
    int PROC();
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

    /*计算最大不模糊速度 prf:脉冲重复频率，procUnfold 脉冲重复比，wavelength 射频波长*/
    int calculateVmax();
    /*计算输出数据中 头数据所占的字节数**/
    int calHdrBytes();


    /*get 、set方法*/
    const char* getAntennaBuf() const;
    double getAzimuth() const;
    void setAzimuth(double azimuth);
    int getClientSocket() const;
    void setClientSocket(int clientSocket);
    int getDataBytesNum() const;
    void setDataBytesNum(int dataBytesNum);
    int getDistance() const;
    void setDistance(int distance );
    unsigned short getDopFilter() const;
    void setDopFilter(unsigned short dopFilter);
    double getElevation() const;
    void setElevation(double elevation);
    const unsigned char* getElevationBuff() const;
    const char* getFormatBuffer() const;
    int getHdrBytesNum() const;
    void setHdrBytesNum(int hdrBytesNum);
    unsigned char getHigh8Bits() const;
    void setHigh8Bits(unsigned char high8Bits);
    unsigned char getInputNBuff() const;
    void setInputNBuff(unsigned char inputNBuff);
    bool isIsWorking() const;
    void setIsWorking(bool isWorking);
    unsigned char getLow8Bits() const;
    void setLow8Bits(unsigned char low8Bits);
    int getLrmskBinsNum() const;
    void setLrmskBinsNum(int lrmskBinsNum);
    unsigned char getLrmskRangeAvg() const;
    void setLrmskRangeAvg(unsigned char lrmskRangeAvg);
    const unsigned char* getOutbuff() const;
    bool isProcArc() const;
    void setProcArc(bool procArc);
    bool isProcKdp() const;
    void setProcKdp(bool procKdp);
    unsigned char getProcMode() const;
    void setProcMode(unsigned char procMode);
    bool isProcT() const;
    void setProcT(bool procT);
    unsigned char getProcTsout() const;
    void setProcTsout(unsigned char procTsout);
    unsigned char getProcTsSubType() const;
    void setProcTsSubType(unsigned char procTsSubType);
    unsigned char getProcUnfold() const;
    void setProcUnfold(unsigned char procUnfold);
    bool isProcV() const;
    void setProcV(bool procV);
    bool isProcW() const;
    void setProcW(bool procW);
    bool isProcZ() const;
    void setProcZ(bool procZ);
    bool isProcZdr() const;
    void setProcZdr(bool procZdr);
    int getRadioFrequency() const;
    void setRadioFrequency(int radioFrequency);
    const char* getRcverStatus() const;
    const char* getRecvBuffer() const;
    int getResolution() const;
    void setResolution(int resolution);
    const char* getSendBuffer() const;
    int getSetpwfPrf() const;
    void setSetpwfPrf(int setpwfPrf);
    int getSetpwfPulseWidth() const;
    void setSetpwfPulseWidth(int setpwfPulseWidth);
    const unsigned char* getSoprm() const;
    float getSoprmCcorThr() const;
    void setSoprmCcorThr(float soprmCcorThr);
    float getSoprmLogThr() const;
    void setSoprmLogThr(float soprmLogThr);
    bool isSoprmNhd() const;
    void setSoprmNhd(bool soprmNhd);
    bool isSoprmNth() const;
    void setSoprmNth(bool soprmNth);
    unsigned short getSoprmProcessMode() const;
    void setSoprmProcessMode(unsigned short soprmProcessMode);
    unsigned short getSoprmPulseAcc() const;
    void setSoprmPulseAcc(unsigned short soprmPulseAcc);
    bool isSoprmR2Enable() const;
    void setSoprmR2Enable(bool soprmR2Enable);
    float getSoprmSigThr() const;
    void setSoprmSigThr(float soprmSigThr);
    float getSoprmSqi() const;
    void setSoprmSqi(float soprmSqi);
    float getSoprmSqiThr() const;
    void setSoprmSqiThr(float soprmSqiThr);
    bool isThreadFlag() const;
    void setThreadFlag(bool threadFlag );
    float getVmax() const;
    void setVmax(float vmax);
    float getWaveLen() const;
    void setWaveLen(float waveLen);
    bool isCfghdrFlg() const;
    void setCfghdrFlg(bool cfghdrFlg);
    bool isCfghdrGpm() const;
    void setCfghdrGpm(bool cfghdrGpm);
    bool isCfghdrMmt() const;
    void setCfghdrMmt(bool cfghdrMmt);
    bool isCfghdrPbn() const;
    void setCfghdrPbn(bool cfghdrPbn);
    bool isCfghdrPrt() const;
    void setCfghdrPrt(bool cfghdrPrt);
    bool isCfghdrPul() const;
    void setCfghdrPul(bool cfghdrPul);
    bool isCfghdrSyt() const;
    void setCfghdrSyt(bool cfghdrSyt);
    bool isCfghdrTag() const;
    void setCfghdrTag(bool cfghdrTag);
    bool isCfghdrTid() const;
    void setCfghdrTid(bool cfghdrTid);
    bool isCfghdrTim() const;
    void setCfghdrTim(bool cfghdrTim);
    bool isCfghdrUtc() const;
    void setCfghdrUtc(bool cfghdrUtc);
};


#endif // RVP900_H
