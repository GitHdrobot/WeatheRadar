#ifndef CONSTRVP900_H
#define CONSTRVP900_H

#define RVP900_HOSTNAME "RVP900"
#define RVP900_PORT 30740
#define SOCKET_CREATE_ERR -2
#define SOCKET_CONN_ERR -3
#define SOCKET_READ_ERR -4
#define SOCKET_SEND_ERR -5
#define SOCKET_RECV_ERR -6
#define NOT_ACK_ERR -7
#define SOCKET_RECV_NOT_CMPLT_ERR -8
#define IOTEST_ERR -9
#define RVP_NO_ERR 0


/*
 * 指令格式为 command_prefix + WIRT/READ + | + command_opcode + | + additional_data
 * 前缀command_prefix长度用8个字节表示，即将发送数据的长度
 * WIRT/READ 表示读写操作
 * command_opcode 实际指令的操作码 用16 bit，两个字节，一个字，4位16进制数表示
 * additional_data表示附加的输入数据 如输入参数等
*/

#define COMMAND_PREFIX_LEN 8 //指令前缀长度
#define COMMAND_WRITE "WRIT" //写指令字符
#define COMMAND_READ "READ" //读指令字符
#define COMMAND_SEP "|"     //分隔字符
#define COMM_WRIT_LEN 4+1+2  //写命令长度 WIRT 4个，| 1个，命令字 2两个


//reset command const 重置指令常量
/*重置指令会将rvp900全部重置
*/
//低8位
#define RESET_OPCODE 0xc  //reset指令操作码 0-4位
#define FLAG_FIF 0x8 //清空FIFO缓冲区 7位
#define RESET_LOW8BIT FLAG_FIF * 0x10 + RESET_OPCODE//低8位

//高8位
#define FLAG_NSE 0x1 //将接收机的噪声恢复至默认值 8位
#define FLAG_NV 0x2 //重新载入配置 9位
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
#define LSYNC_LOW8BIT 0x11
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
/*
* LRMSK command const, load range mask
* 载入距离掩码，距离掩码的作用主要是更加灵活的设置收集数据的距离库
*/
#define LRMSK_PREFIX "00000007"
#define LRMSK_N "LRMSK"
#define LRMSK_OPCODE 0x01
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
#define LFILT_N "LFILT"
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
#define SETPWF_OPCODE 0x10
#define SETPWF_L8BIT SETPWF_OPCODE
#define SETPWF_H8BIT 0x0

/*
*SNOISE commd const,sample noise level
*估计接收机的噪声级
*/
#define SNOISE_PREFIX "00000011"
#define SNOISE_OPCODE 0x05
#define SNOISE_L8BIT SETPWF_OPCODE
#endif // CONSTRVP900_H

