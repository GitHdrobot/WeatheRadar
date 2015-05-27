#ifndef UARTCOMM_H
#define UARTCOMM_H

#include <stdio.h> //printf等用到
#include <fcntl.h> //file control
#include <string.h> //bzero等用到
#include <stdlib.h> //exit(0)等用到
#include <sys/times.h>//sleep等用到
#include <termios.h>//串口应用程序必须添加的头文件
#include <sys/types.h>//定义pid_t,size等
#include <unistd.h>//read,write,getpid等等
#include <sys/ioctl.h>//ioctl


#define TTY_DEV0 "/dev/ttyS0" //端口路径 如果是在电脑端选择ttyUSB,在mini2440端则选择ttySAC
#define TTY_DEV1 "/dev/ttyS1"
#define TTY_DEV2 "/dev/ttyS2"
#define TTY_DEV3 "/dev/ttyS3"
#define TTY_DEV4 "/dev/ttyUSB0"
#define TTY_DEV5 "/dev/ttyUSB1"
#define TIMEOUT_SEC(buflen,baud) (buflen*20/baud+2)//接收超时
#define TIMEOUT_USEC 0

typedef struct //define the uart value struct
{
    char    prompt;         //prompt after reciving data
    int     baudrate;       //baudrate
    char    databit;        //data bits, 5, 6, 7, 8
    char    debug;          //debug mode, 0: none, 1: debug
    char    echo;           //echo mode, 0: none, 1: echo
    char    fctl;           //flow control, 0: none, 1: hardware, 2: software
    char    tty;            //tty: 0, 1, 2, 3, 4, 5, 6, 7
    char    parity;         //parity 0: none, 1: odd, 2: even
    char    stopbit;        //stop bits, 1, 2
    //const int reserved;   //reserved, must be zero
    int reserved;           //reserved, must be zero
}portinfo_t;
typedef portinfo_t *pportinfo_t; //redefine the portinfo_t

/*串口通信控制类*/
class UartComm
{
public:
    UartComm();
    ~UartComm();

    int MK1=0;
    int MK2=0;

    char    prompt;         //prompt after reciving data
    int     baudrate;       //baudrate
    char    databit;        //data bits, 5, 6, 7, 8
    char    debug;          //debug mode, 0: none, 1: debug
    char    echo;           //echo mode, 0: none, 1: echo
    char    fctl;           //flow control, 0: none, 1: hardware, 2: software
    char    tty;            //tty: 0, 1, 2, 3, 4, 5, 6, 7
    char    parity;         //parity 0: none, 1: odd, 2: even
    char    stopbit;        //stop bits, 1, 2
    //const int reserved;   //reserved, must be zero
    int reserved;           //reserved, must be zero
public:

    int PortOpen(pportinfo_t pportinfo);                   //open the uart
    int PortSet(int fdcom, const pportinfo_t pportinfo);   //set the uart
    void PortClose(int fdcom);                             //close the uart
    int PortSend(int fdcom, char *data, int datalen);      //send the datas
    int PortRecv(int fdcom, char *data, int datalen, int baudrate);//receive the datas
    int PortSend_1(int fdcom, char *data, int datalen);
    static char *get_ptty(pportinfo_t pportinfo);
    static int convbaud(unsigned long int baudrate);

    int getBaudrate() const ;
    void setBaudrate(int baudrate) ;
    char getDatabit() const ;
    void setDatabit(char databit) ;
    char getDebug() const ;
    void setDebug(char debug) ;
    char getEcho() const ;
    void setEcho(char echo) ;
    char getFctl() const ;
    void setFctl(char fctl) ;
    char getParity() const ;
    void setParity(char parity) ;
    char getPrompt() const ;
    void setPrompt(char prompt) ;
    int getReserved() const ;
    void setReserved(int reserved) ;
    char getStopbit() const ;
    void setStopbit(char stopbit) ;
    char getTty() const ;
    void setTty(char tty) ;


};
#endif // UARTCOMM_H
