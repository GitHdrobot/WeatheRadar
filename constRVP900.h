/*
*RVP900的一些常量设置 主要包括指令部分
*/

#ifndef CONSTRVP900_H
#define CONSTRVP900_H

#define RVP900_HOSTNAME "RVP900"    //主机名
#define RVP900_PORT 30740   //端口号
#define SOCKET_CREATE_ERR -2    //创建SOCKET错误
#define SOCKET_CONN_ERR -3      //SOCKET连接错误
#define SOCKET_READ_ERR -4      //SOCKET读取错误
#define SOCKET_SEND_ERR -5      //SOCKET发送错误
#define SOCKET_RECV_ERR -6      //SOCKET接受错误
#define NOT_ACK_ERR -7          //RVP9未响应错误
#define SOCKET_RECV_NOT_CMPLT_ERR -8    //SOCKET接收不完全错误
#define IOTEST_ERR -9       //IOTEST测试错误
#define RVP_NO_ERR 0        //无错误


/*
 * 指令格式为 command_prefix + WIRT/READ + | + command_opcode + | + additional_data
 * 前缀command_prefix长度用8个字节表示，即将发送数据的长度
 * WIRT/READ 表示读写操作
 * command_opcode 实际指令的操作码 用16 bit，两个字节，一个字，4位16进制数表示
 * additional_data表示附加的输入数据 如输入参数等
*/

#define COMMAND_PREFIX_LEN 8 //指令前缀长度
#define COMMAND_WRITE "WRIT" //写指令字符
const unsigned char commandWrite[] = "WRIT";
#define COMMAND_READ "READ" //读指令字符
const unsigned char commandRead[] = "READ";
#define COMMAND_SEP "|"     //分隔字符
const unsigned char commandSep = '|';
#define COMM_WRIT_LEN 4+1+2  //写命令长度 WIRT 4个，| 1个，命令字 2两个

#define SET_ZERO 0 //置0
#define SET_ONE 1 //置1

//reset command const 重置指令常量
/*重置指令会将rvp900全部重置
*/
//低8位
#define RESET_OPCODE 0xc  //reset指令操作码 0-4位
/*第5位置1 设置该位 表示载入已保存的设置 以兼容RVP6、7*/
#define RESET_5thBIT_NV  0x20
/*第6位置1 设置该位 表示载入已保存的设置 以兼容RVP6、7*/
#define RESET_6thBIT_NV  0x40
/*第7位置1 设置该位  表示将删除所以当前输出缓冲区FIFO的所有数据
*该命令将会清掉上次命令执行后的输出数据，这样可以重新读入新的输出数据
*/
#define RESET_7thBIT_FIF  0x80


#define RESET_LOW8BIT RESET_7thBIT_FIF + RESET_OPCODE//低8位

//高8位
/*第8位置1 设置该位 表示将接收机对于所有脉冲宽度（在Mt中设置）的噪声水平
 *设置到加电默认值*/
#define RESET_8thBIT_NSE  0x100
/*第9位置1 设置该位 表示载入已保存的设置 以兼容RVP6、7*/
#define RESET_9thBIT_NV  0x200

#define RESET_HIGH8BIT 0x0//高8位

#define RESET_PREFIX "00000007"
#define RESET_COMM_LEN COMM_WRIT_LEN //len("WRIT")+len("|")+2
#define RESET_LEN COMMAND_PREFIX_LEN + RESET_COMM_LEN
#define RESET_FIFO "RKFF"  //Reset kernel FIFO
#define STAT_FIFO "STAT"  //Status of FIFO,1 means has data avaliable in fifo

//IOTEST command const，输入输出测试指令常量
/*发送16个字，32个字节的序列，存放任意的数，RVP900会复制这32个字节的内容
*再读取该32个字节 若与发送的相等 则说明没有出故障的数据总线
*/
//该命令的命令字中只有操作码
//0-4 bit
#define IOTEST_OPCONDE 0x3
//低8位
#define IOTEST_LOW8BIT IOTEST_OPCONDE
//高8位
#define IOTEST_HIGH8BIT 0x0//高8位
#define ADD_DATA_LEN 32 //输入参数数据长度32字节
#define IOTEST_COMM_LEN COMMAND_PREFIX_LEN + COMM_WRIT_LEN + ADD_DATA_LEN
#define IOTEST_PREFIX "000000039"


/*
*LSYNC command const ,加载 天线同步表
*/
#define LSYNC "LSYNC"
//low 8bit
/*0-4位*/
#define LSYNC_OPCODE 0x11
#define LSYNC_LOW8BIT LSYNC_OPCODE

//high 8bit
/*设置该位表示该命令后是新的一个表的大小和数组值。若Ld=0，
 *那么LSYNC只是一个字的命令。否则，后面的字用来载入新的表。
 */
#define LSYNC_8thBIT_LD 0x100
/*指定TAG角度输入时4位BCD码，否则假设角度为16位的二进制码*/
#define LSYNC_9thBIT_BCD 0x200
/*同步是基于TAG1531（仰角）输入，否则是使用TAG015（相位）*/
#define LSYNC_10thBIT_E1 0x400
/*打开天线同步功能*/
#define LSYNC_11thBIT_ENA 0x800
/*该位表示 由于CPI的特点经常会导致全部的射线
 *被丢掉，脉冲个数少于预期个数时，允许使用短的射线
 *此时，设置该位，用户需要编写代码检查进入每条射线的实际的脉冲数
 *并且手工丢弃那些太短而不能包含有用数据的射线
*/
#define LSYNC_12thBIT_SHT 0x1000
/*没看明白 设置角宽是固定的还是动态变化的？*/
#define LSYNC_13thBIT_DYN 0x2000

#define LSYNC_HIGH8BIT 0x20
#define LSYNC_PREFIX "00000007"
#define LSYNC_LEN COMMAND_PREFIX_LEN+COMM_WRIT_LEN

/*
*SOPRM 设置操作参数
*/
#define SOPRM_N "SOPRM"
#define SOPRM_PREFIX "00000057"

/*
*CFGHDR command const，configure Ray header words
*配置射线头信息
*/
#define CFGHDR_N "CFGHDR"
#define CFGHDR_PREFIX "00000011"

#define CFGHDR_OPCODE 0x5f
#define CFGHDR_TAG 0x01
#define CFGHDR_PRT 0x02
#define CFGHDR_PUL 0x04
#define CFGHDR_TIM 0x08
#define CFGHDR_GPM 0x10
#define CFGHDR_FLG 0x20
#define CFGHDR_UTC 0x40
#define CFGHDR_MMT 0x80
#define CFGHDR_SYT 0x100
#define CFGHDR_PBN 0x200
#define CFGHDR_TID 0x400

/*
* LRMSK command const, load range mask
* 载入距离掩码，距离掩码的作用主要是更加灵活的设置收集数据的距离库
*/
#define LRMSK_PREFIX "00000007"
#define LRMSK_OPCODE 0x01
const unsigned char lrmskOpCode = 0x01;
//lrmsk 1 word;input#1 - input#512 512 word;
const unsigned char lrmskCommLen[] = "00001031";

#define LRMSK_L8BIT LRMSK_OPCODE
#define LRMSK_H8BIT_Z 0x0   //表示距离平均因子
#define LRMSK_H8BIT_O 0x1   //表示距离平均因子
#define LRMSK_MSK_NUM 1024 //距离掩码的位数
#define LRMSK_IN_PREFIX "00001029" //距离掩码命令输入参数的长度

/*
*LFILT command const，Load clutter filter flags
*设置杂波滤波器
*/
#define LFILT_PREFIX "00000007"
#define LFILT_OPCODE 0x28
#define LFILT_L8BIT LFILT_OPCODE
#define LFILT_H8BIT 0x0
#define LFILT_INP_PRE "00006149"  //LFILT输入参数前缀
#define LFILT_INP_LEN 3072  //LFILT输入长度
#define LFILT_MSG_LEN LFILT_INP_LEN * 2 + COMMAND_PREFIX_LEN + 5  //LFILT输入长度
/*
*SETPWF command const,set pulse width and prf
*设置脉冲宽度和脉冲重复频率
*/
#define SETPWF_PREFIX "00000009"

const unsigned char setpwfOpCode = 0x10;//指令SETPWF操作码
const unsigned char setpwfL8Bit = setpwfOpCode;
const unsigned char setpwfH8Bit = 0x0;

/*
*SNOISE commd const,sample noise level
*估计接收机的噪声级
*/
#define SNOISE_PREFIX "00000011"
const unsigned char snoiseOpCode = 0x05;
const unsigned char snoiseL8Bit = snoiseOpCode;

/*
*PROC command const,initiate processing
*初始化数据处理
*/
#define PROC_FREFIX "00000007"
const unsigned char procOpCode = 0x06 ;

/*
*GPARM command const,get processor parameters
*获取处理器状态信息
*/
#define GPARM_PREFIX "00000007"
#define GPARM_L8BIT 0x09
#define GPARM_H8BIT 0x00

const unsigned char gparmL8bit = 0x09;
const unsigned char gparmH8bit = 0x00;

#define BIT_CLEAR 0x0
#define BYTE_CLEAR 0x0


//双PRF 比 常量 设置的是PROC命令的8、9位
const unsigned char procUnfoldNone = 0x00;
const unsigned char procUnfold2To3 = 0x01;
const unsigned char procUnfold3To4 = 0x10;
const unsigned char procUnfold4To5 = 0x11;

const unsigned char procSyncModec = 0x01;
const unsigned char procFreeRunModec = 0x10;
const unsigned char procTimeSerisModec = 0x11;

const unsigned short disrange_10 = 10;
const unsigned short disrange_20 = 20;
const unsigned short disrange_30 = 30;
const unsigned short disrange_50 = 50;
const unsigned short disrange_100 = 100;
const unsigned short disrange_150 = 150;
const unsigned short disrange_300 = 300;

//processing mode PPP,FFT,RPP,DPRT_1,DPRT_2
const unsigned short soprmProcessModePPP = 1;
const unsigned short soprmProcessModeFFT = 2;
const unsigned short soprmProcessModeRPP = 3;
const unsigned short soprmProcessModeDPRT_1 = 4;
const unsigned short soprmProcessModeDPRT_2 = 5;

//最大的反射率因子
const  short dBZMax = 70;
//最小的反射率因子
const  short dBZMin = -10;

//Rnv  "距离订正通断" ;
//R2_Enable  "R2使能"  ;
//CMS  "单库杂波消除";
//Lsr "强度斑点消除";
//Dsr "速度斑点消除";
//窗口类型
//0:Rectangular, 1:Hamming, 2:Blackman, 3:Exact
//Blackman, 4:VonHann.
#endif // CONSTRVP900_H
