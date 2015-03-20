#ifndef RVP900_H
#define RVP900_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
//rvp900 控制类
#include "constRVP900.h"

class RVP900
{
public:
    RVP900();
    ~RVP900();
    int connectRVP();//连接到server socket
    int openRVP900();//发送一组命令 打开RVP900
    int readSocketResp();//读取rvp900响应信息
    int assembleCmdMsg(int length,char *cmd,char *data);//构造要发送的命令的信息
    int sendMsg(char *buffer,int length);//向RVP900发送数据
    int getRvp900status(char *buffer);//获取RVP900的状态信息
    int readData(char *Buffer,int length);//从RVP900中读取数据
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
    int LoadSync();
    /*
    *setup opertating parameters, The command
    *should be issued whenever any of the parameters in the list change. The
    *default parameter list consists of twenty 16-bit input words
    *设置操作参数,当列表中 参数有改变时 则需执行该命令。默认的参数列表由20个16位输入字组成
    */
    int setOperPRM();
    /*
    *The processed data that are output by the PROC command may contain
    optional header words that give additional information about each ray.
    This command configures the set of words that makeup each header. There
    are (up to) thirty two different choices of words or groups of words to
    include, as indicated by the bit mask following the command.
    PROC命令处理后的输出数据可能包含可选的头字数据，这些头字可以提供关于每条射线额外的信息
    该命令配置字集，这些字集组成每个头。一共有32个不同的字、字组选择，由命令后面的位掩码表示
    */
    int ConFGHDR();
    /*
    *This command informs the signal processor of the ranges at which data are
    *to be collected. An arbitrary set of range bins are selected via an 8192-bit
    *mask.
    *该命令指示信号处理器在哪些位置收集数据。通过8192个掩码位来选择一个任意的距离库集合
    *距离库产生公式：RES*（N-1），N表示第N位，RES表示距离分辨率
    */
    int loadRanMsk(char* buffer,int ranMark);
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
public:
    int  clientSocket;
    char pulseRati;
    char sendBuffer[1024*8];//发送数据buffer
    char recvBuffer[1024*8];//接收数据buffer
    unsigned char LDRNV[504];
    unsigned char SOPRM[52];
    char PulseRatio;
};

#endif // RVP900_H
