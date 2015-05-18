#include "uartcomm.h"

UartComm::UartComm()
{

}

UartComm::~UartComm()
{

}


/*************************************************
fuction:     char *get_ptty(pportinfo_t pportinfo)
description: get thd uart name
return：     ptty
**************************************************/
static char *UartComm::get_ptty(pportinfo_t pportinfo)
{
    char *ptty=NULL;
    switch(pportinfo->tty)
    {
    case '0':
        ptty=TTY_DEV0;
        break;
    case '1':
        ptty=TTY_DEV1;
        break;
    case '2':
        ptty=TTY_DEV2;
        break;
    case '3':
        ptty=TTY_DEV3;
        break;
    case '4':
        ptty=TTY_DEV4;
        break;
    case '5':
        ptty=TTY_DEV5;
        break;
    }
    return ptty;
}
/*************************************************
fuction:     convbaud(unsigned long int baudrate)
description: baud change
return：     ptty
**************************************************/
static int UartComm::convbaud(unsigned long int baudrate)
{
    switch(baudrate){
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    default:
        return B9600;
    }
}
/****************************************************************
fuction:     convbaud(unsigned long int baudrate)
description: set the uart
parameters:  fdcom: 串口文件描述符，
             pportinfo： 待设置的串口信息
return：     tmp
******************************************************************/
int UartComm::PortSet(int fdcom, const pportinfo_t pportinfo)
{
    struct termios termios_old, termios_new;
    int         baudrate, tmp;
    char        databit, stopbit, parity, fctl;
    bzero(&termios_old, sizeof(termios_old));//置字符串前sizeof个字节为零
    //tcgetattr(fdcom, &termios_old);
    bzero(&termios_new, sizeof(termios_new));
    cfmakeraw(&termios_new);//设置终端属性
    tcgetattr(fdcom, &termios_old);//get the serial port attributions
    tcgetattr(fdcom,&termios_new);
    /*------------设置端口属性----------------*/
    //baudrates
    baudrate = convbaud(pportinfo -> baudrate);//得到波特率
    cfsetispeed(&termios_new, baudrate);//填入串口输入端的波特率
    cfsetospeed(&termios_new, baudrate);//填入串口输出端的波特率
    termios_new.c_cflag |= CLOCAL|CREAD;//控制模式，保证程序不会成为端口的占有者
    // 控制模式，flow control
    fctl = pportinfo-> fctl;
    switch(fctl){
    case '0':{
        termios_new.c_cflag &= ~CRTSCTS;//no flow control
    }break;
    case '1':{
        termios_new.c_cflag |= CRTSCTS;//hardware flow control
    }break;
    case '2':{
        termios_new.c_iflag |= IXON | IXOFF |IXANY; //software flow control
    }break;
    }
    //控制模式，data bits
    termios_new.c_cflag &= ~CSIZE;//控制模式，屏蔽字符大小位
    databit = pportinfo -> databit;
    switch(databit){
    case '5':
        termios_new.c_cflag |= CS5;
    case '6':
        termios_new.c_cflag |= CS6;
    case '7':
        termios_new.c_cflag |= CS7;
    default:
        termios_new.c_cflag |= CS8;
    }
    //控制模式 parity check
    parity = pportinfo -> parity;
    switch(parity){
    case '0':{
        termios_new.c_cflag &= ~PARENB;//no parity check
    }break;
    case '1':{
        termios_new.c_cflag |= PARENB;//odd check
        termios_new.c_cflag &= ~PARODD;
    }break;
    case '2':{
        termios_new.c_cflag |= PARENB;//even check
        termios_new.c_cflag |= PARODD;
    }break;
    }
    //控制模式，stop bits
    stopbit = pportinfo -> stopbit;
    if(stopbit == '2'){
        termios_new.c_cflag |= CSTOPB;//2 stop bits
    }
    else{
        termios_new.c_cflag &= ~CSTOPB;//1 stop bits
    }
    //other attributions default
    termios_new.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);//输入模式,原始数据输入
    termios_new.c_cc[VTIME] = 200;
    termios_new.c_cc[VMIN] = 8;
    tcflush(fdcom, TCIOFLUSH);//溢出的数据可以接收，但不读
    tmp = tcsetattr(fdcom, TCSANOW, &termios_new);//设置新属性，TCSANOW：所有改变立即生效      tcgetattr(fdcom, &termios_old);
    return(tmp);
}
/****************************************************************
fuction:     PortOpen(pportinfo_t pportinfo)
description: open serial port
parameters:  pportinfo： 待设置的串口信息
return：     fdcom:文件描述符
******************************************************************/
int UartComm::PortOpen(pportinfo_t pportinfo)
{
    int fdcom;      //串口文件描述符
    char *ptty;
    ptty = get_ptty(pportinfo);
    //fdcom = open(ptty, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
    fdcom = open(ptty, O_RDWR | O_NOCTTY | O_NDELAY);
    fcntl(fdcom,F_SETFL,0);
    return (fdcom);
}
/****************************************************************
fuction:     PortClose(int fdcom)
description: close serial port
parameters:  fdcom:文件描述符
return：      NONE
******************************************************************/
void UartComm::PortClose(int fdcom)
{
    close(fdcom);
}
/****************************************************************
fuction:     PortSend(int fdcom, char *data, int datalen)
description: close serial port
parameters:  fdcom: 串口描述符，data: 待发送数据，datalen: 数据长度
return：     len:实际长度
******************************************************************/
int UartComm::PortSend(int fdcom, char *data, int datalen)
{
    int len = 0;

    //printf("datalen=%d ",datalen);

    for(;;)
    {
        if(MK2==0)
            break;
    }
    MK1=-1;
    //len = write(fdcom, data, datalen);//实际写入的长度

    for(len=0;len<datalen;len++)
    {
        int l=write(fdcom, data+len, 1);
        //for(int k=0;k<600000;k++)
        //n=0;
        //sleep (1);
        if (l!=1)
            break;
    }
    /*if(len == datalen)
        {
            printf("write successful %s\n",data);
        }
        else
            printf("write failed");*/
    MK1=0;
    /*if(len == datalen)
        {
                return (len);
        }
        else{
                tcflush(fdcom, TCOFLUSH);
                return -1;
        }*/
    return len;

}
/****************************************************************
fuction:     PortRecv(int fdcom, char *data, int datalen, int baudrate)
description: receive the datas
parameters:  fdcom：串口描述符， data：接收缓冲区, datalen：接收长度，
             baudrate：波特率
return：     readlen:实际读入的字节数
******************************************************************/
int UartComm::PortRecv(int fdcom, char *data, int datalen, int baudrate)
{
    int readlen, fs_sel;
    fd_set      fs_read;
    struct timeval tv_timeout;

    FD_ZERO(&fs_read);
    FD_SET(fdcom, &fs_read);
    tv_timeout.tv_sec = TIMEOUT_SEC(datalen, baudrate);
    tv_timeout.tv_usec = TIMEOUT_USEC;
    fs_sel = select(fdcom+1, &fs_read, NULL, NULL, &tv_timeout);
    if(fs_sel)
    {
        readlen = read(fdcom, data, datalen);
        return(readlen);
    }
    else
    {
        return(-1);
    }
    return (readlen);
}

int UartComm::PortSend_1(int fdcom, char *data, int datalen)
{
    int len = 0;

    for(;;)
    {
        if(MK1==0)
            break;
    }
    MK2=-1;
    len = write(fdcom, data, datalen);//实际写入的长度
    /*if(len > 0)
    {
        printf("write successful %s\n",data);
    }
    else
        printf("write failed");*/
    MK2=0;
    if(len == datalen)
    {
        return (len);
    }
    else
    {
        tcflush(fdcom, TCOFLUSH);
        return -1;
    }

}



int UartComm::getBaudrate() const {
    return baudrate;
}

void UartComm::setBaudrate(int baudrate) {
    this->baudrate = baudrate;
}

char UartComm::getDatabit() const {
    return databit;
}

void UartComm::setDatabit(char databit) {
    this->databit = databit;
}

char UartComm::getDebug() const {
    return debug;
}

void UartComm::setDebug(char debug) {
    this->debug = debug;
}

char UartComm::getEcho() const {
    return echo;
}

void UartComm::setEcho(char echo) {
    this->echo = echo;
}

char UartComm::getFctl() const {
    return fctl;
}

void UartComm::setFctl(char fctl) {
    this->fctl = fctl;
}

char UartComm::getParity() const {
    return parity;
}

void UartComm::setParity(char parity) {
    this->parity = parity;
}

char UartComm::getPrompt() const {
    return prompt;
}

void UartComm::setPrompt(char prompt) {
    this->prompt = prompt;
}

int UartComm::getReserved() const {
    return reserved;
}

void UartComm::setReserved(int reserved) {
    this->reserved = reserved;
}

char UartComm::getStopbit() const {
    return stopbit;
}

void UartComm::setStopbit(char stopbit) {
    this->stopbit = stopbit;
}

char UartComm::getTty() const {
    return tty;
}

void UartComm::setTty(char tty) {
    this->tty = tty;
}
