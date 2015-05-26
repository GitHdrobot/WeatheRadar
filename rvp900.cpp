#include "rvp900.h"






RVP900::RVP900()
{


}

RVP900::~RVP900()
{

}
int RVP900::reset(){
    //    if(int s= comboCmdMsg(RESET_FIFO,"2",8) != 0){//Reset out FIFO
    //        return s;
    //    }
    //    if(int s = readSocketResp()!=0){
    //        return s;
    //    }
    /*status of FIFO
    *1 means has data avalible in output buffer
    */
    //    if(int s= comboCmdMsg(STAT_FIFO,"2",8) != 0){
    //        return s;
    //    }
    //    if(int s = readSocketResp()!=0){
    //        return s;
    //    }
    // if(((recvBuffer[4]-'0')&0x1)==0){
    sendBuffer[0] = 0;
    strcat(sendBuffer,RESET_PREFIX);//8bit
    strcat(sendBuffer,COMMAND_WRITE);//4bit
    strcat(sendBuffer,COMMAND_SEP);//1bit
    sendBuffer[13] = RESET_LOW8BIT;
    sendBuffer[13] = RESET_HIGH8BIT;
    sendBuffer[RESET_LEN] = 0;
    if(int s = sendMsg(sendBuffer,RESET_LEN) !=RVP_NO_ERR){
        return s ;
    }return RVP_NO_ERR;
    // }


}
int RVP900::IOTest(){
    sendBuffer[0] = 0;
    strcat(sendBuffer,IOTEST_PREFIX);//8bit
    strcat(sendBuffer,COMMAND_WRITE);//4bit
    strcat(sendBuffer,COMMAND_SEP);//1bit
    sendBuffer[13] = IOTEST_LOW8BIT;
    sendBuffer[14] = IOTEST_HIGH8BIT;
    for(int i=COMMAND_PREFIX_LEN + COMM_WRIT_LEN;i<IOTEST_COMM_LEN;i++){
        sendBuffer[i] = i;
    }
    sendBuffer[IOTEST_COMM_LEN]=0;
    if(sendMsg(sendBuffer,IOTEST_COMM_LEN)!=RVP_NO_ERR){
        return SOCKET_SEND_ERR;
    }
    if(int s = readSocketResp()!= RVP_NO_ERR){
        return s;
    }
    if(int s = comboCmdMsg(COMMAND_READ,"32",9)!=RVP_NO_ERR){
        return s;
    }
    if(int s = readSocketResp()!= RVP_NO_ERR){
        recvBuffer[4+32] = 0;
        printf("%s\n",recvBuffer);
        return SOCKET_READ_ERR;
    }
    for(int i=0;i<32;i++){
        if(recvBuffer[4+i] != i){
            return IOTEST_ERR;
        }
    }
    return RVP_NO_ERR;
}

int RVP900::loadSync(){
    sendBuffer[0]=0;
    strcat(sendBuffer,LSYNC_PREFIX);//8bit
    strcat(sendBuffer,COMMAND_WRITE);//4bit
    strcat(sendBuffer,COMMAND_SEP);//1bit
    sendBuffer[13] = LSYNC_LOW8BIT;
    sendBuffer[14] = LSYNC_HIGH8BIT;

    if(int s = sendMsg(sendBuffer,LSYNC_LEN)!= RVP_NO_ERR){
        return s;
    }
    if(int s= readSocketResp()!=RVP_NO_ERR){
        return s;
    }
    //以下不明白什么原因
    sendBuffer[0]=0;
    strcat(sendBuffer,"00000011WRIT|");//OP_LSYNC
    sendBuffer[13]=0x11;
    sendBuffer[14]=0x01;
    sendBuffer[15]=0x68;
    sendBuffer[16]=0x01;
    sendBuffer[17]=0x0;
    sendBuffer[18]=0x0;
    if ((sendMsg(sendBuffer,19))!=0)
        return -16;
    if (readSocketResp()!=0)
        return -17;

    sendBuffer[0]=0;
    strcat (sendBuffer,"00000725WRIT|");//OP_LSYNC
    for (int i=0;i<360;i++)
    {
        float ang=(float)i*65536.0/360.0;
        int iang=ang;
        sendBuffer[13+i*2+0]=iang%256;
        sendBuffer[13+i*2+1]=iang/256;
    }
    if ((sendMsg(sendBuffer,733))!=0)
        return -18;
    if (readSocketResp()!=0)
        return -19;

    sendBuffer[0]=0;
    strcat (sendBuffer,"00000007WRIT|");//OP_LSYNC
    sendBuffer[13]=0x11;
    sendBuffer[14]=0x20;
    if ((sendMsg(sendBuffer,15))!=0)
        return -20;
    if (readSocketResp()!=0)
        return -21;
    return RVP_NO_ERR;
}

/*
* 设置操作参数
*/
int RVP900::setOperPRM(){
    sendBuffer[0]=0;
    strcat (sendBuffer,SOPRM_PREFIX);//OP_SOPRM
    strcat (sendBuffer,COMMAND_WRITE);
    strcat (sendBuffer,COMMAND_SEP);
    for (int i=0;i<52;i++)
        sendBuffer[13+i]=soprm[i];
    if ((sendMsg(sendBuffer,65))!=0)
        return SOCKET_READ_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}
/*
*CFGHDR 配置射线头字节
*/
int RVP900::CFGHDR(){
    sendBuffer[0]=0;
    low8Bits = 0x00;
    high8Bits = 0x00;
    strcat(sendBuffer,CFGHDR_PREFIX);//OP_CFGHDR
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    low8Bits = CFGHDR_OPCODE;
    sendBuffer[13]=low8Bits;
    sendBuffer[14]=high8Bits;
    if(cfghdrTag){
        inputNBuff += CFGHDR_TAG;
    }
    if(cfghdrPRT){
        inputNBuff += CFGHDR_PRT;
    }
    if(cfghdrPul){
        inputNBuff += CFGHDR_PUL;
    }
    if(cfghdrPul){
        inputNBuff += CFGHDR_TIM;
    }
    if(cfghdrGpm){
        inputNBuff += CFGHDR_GPM;
    }
    if(cfghdrFlg){
        inputNBuff += CFGHDR_FLG;
    }
    if(cfghdrUTC){
        inputNBuff += CFGHDR_UTC;
    }
    sendBuffer[15]=inputNBuff;
    inputNBuff = 0x00;
    if(cfghdrMMT){
        inputNBuff += CFGHDR_MMT;
    }
    if(cfghdrSYT){
        inputNBuff += CFGHDR_SYT;
    }
    if(cfghdrPBN){
        inputNBuff += CFGHDR_PBN;
    }
    if(cfghdrTID){
        inputNBuff += CFGHDR_TID;
    }
    sendBuffer[16] = inputNBuff;
    sendBuffer[17] = BYTE_CLEAR;
    sendBuffer[18] = BYTE_CLEAR;

    hdrBytesNum = calHdrBytes();

    if ((sendMsg(sendBuffer,19))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}
//load range mask
int RVP900::loadRanMsk(int rangeMark){
    sendBuffer[0]=0;
    //距离掩码设置的掩码位个数
    int markNums = (rangeMark % resolution ==0)?(rangeMark/resolution):(rangeMark/resolution+1);
    strcat (sendBuffer,lrmskCommLen);//lrmsk指令的长度
    strcat (sendBuffer,commandWrite);
    strcat (sendBuffer,commandSep);
    sendBuffer[13]=lrmskOpCode; //距离掩码指令操作码
    sendBuffer[14]= lrmskRangeAvg;    //距离平均
    lrmskBinsNum = markNums / (lrmskRangeAvg+1);//计算出输出的库个数
//    /*要先发一次？？？**/
//    if ((sendMsg(sendBuffer,15))!=0)
//        return SOCKET_SEND_ERR;
//    if (readSocketResp()!=0)
//        return SOCKET_READ_ERR;

//    sendBuffer[0]=0;
//    strcat (sendBuffer,LRMSK_IN_PREFIX);//距离掩码输入参数
//    strcat (sendBuffer,COMMAND_WRITE);//写入指令
//    strcat (sendBuffer,COMMAND_SEP);//指令参数分隔符

    for (int i=0;i<markNums;i++)   //设置对应的距离掩码位
    {
        sendBuffer[13+i]=0xff;
        //sendBuffer[13+i*2+1]=0xff;
    }
    for (int i=markNums;i<512;i++)
    {
        sendBuffer[13+i*2+0]=0;
        sendBuffer[13+i*2+1]=0;
    }
    //8个字节的长度，4个字节的“WRIT”，1个字节的“|”，2个字节的命令字，1024个字节的输入数据
    if ((sendMsg(sendBuffer,1039))!=0)//发送信息
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}

int RVP900::setLFILT(char *buffer){
    sendBuffer[0]=0;
    strcat(sendBuffer,LFILT_PREFIX);
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    sendBuffer[13]=LFILT_L8BIT;
    sendBuffer[14]=LFILT_H8BIT;
    if ((sendMsg(sendBuffer,15))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    sendBuffer[0]=0;
    strcat (sendBuffer,LFILT_INP_PRE);//OP_LRFILT
    strcat (sendBuffer,COMMAND_WRITE);
    strcat (sendBuffer,COMMAND_SEP);
    for (int i=0;i<LFILT_INP_LEN;i++)
    {
        sendBuffer[13+i*2+0]=buffer[1];
        sendBuffer[13+i*2+1]=0;
    }
    if ((sendMsg(sendBuffer,LFILT_MSG_LEN))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}

int RVP900::setPulWidth(char *buffer)
{
    sendBuffer[0]=0;
    strcat(sendBuffer,SETPWF_PREFIX);
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    sendBuffer[13]=0x10;
    for(int i=0;i<3;i++)
        sendBuffer[14+i]=buffer[i];
    if ((sendMsg(sendBuffer,17))!=RVP_NO_ERR)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=RVP_NO_ERR)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}
int RVP900::samNoise(){
    sendBuffer[0]=0;
    strcat(sendBuffer,SNOISE_PREFIX);
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    sendBuffer[13]=SNOISE_L8BIT;
    sendBuffer[14]=0;
    sendBuffer[15]=0;
    sendBuffer[16]=0;
    sendBuffer[17]=0;
    sendBuffer[18]=0;
    if((sendMsg(sendBuffer,19))!=RVP_NO_ERR)
        return SOCKET_SEND_ERR;
    if(readSocketResp()!=RVP_NO_ERR)
        return SOCKET_READ_ERR;

    return RVP_NO_ERR;
}
int RVP900::PROC(){
    low8Bits = 0x00;
    high8Bits = 0x00;
    sendBuffer[0]=0;
    strcat(sendBuffer,PROC_FREFIX);
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    low8Bits = PROC_BS_OPCODE;  //PROC command opcode0x06   0-4

    //8-9
    high8Bits  = +procUnfold;
    //    if(procUnfold == PRF_NONE){//双PRF比率
    //        high8Bits   +=   PROC_UNFOLD_NONE;
    //    }else if(procUnfold = PRF_2TO3){
    //        high8Bits   +=   PROC_UNFOLD_2TO3;
    //    }else if(procUnfold = PRF_3TO4){
    //        high8Bits   +=   PROC_UNFOLD_3TO4;
    //    }else if(procUnfold = PRF_4TO5){
    //        high8Bits   +=   PROC_UNFOLD_4TO5;
    //    }
    //5-6
    if(procMode == procTimeSerisModec){//时间序列模式
        low8Bits += 0x11<<5;
        //10-13
        if(procTSSubType){
            high8Bits += procTSOUT<<2;
        }
        //14-15
        /*
        * TSOUT Selects type of data to be output
       00 : 8-bit Time Series 01 : Power Spectrum
       10 : 16-bit Time Series 11 : Unused
        */
        if(procTSOUT){
            high8Bits += procTSOUT<<6;
        }

    }else{
        //5-6
        if(procMode == procSyncModec){
            low8Bits += 0x01<<5;
        }else if(procMode == procFreeRunModec){
            low8Bits += 0x10<<5;
        }
        //7
        if(procKDP){
            low8Bits += 0x01<<7;//KDP第7位
        }
        sendBuffer[13] = low8Bits;

        //10th bit
        if(procZDR){
            high8Bits   +=  0x01<<2;
        }
        //11th bit
        if(procW){
            high8Bits   +=  0x01<<3;
        }
        //12
        if(procV){
            high8Bits   +=  0x01<<4;
        }
        //13
        if(procT){
            high8Bits   +=  0x01<<5;
        }
        //14
        if(procZ){
            high8Bits   +=  0x01<<6;
        }
        //15
        if(procArc){
            high8Bits   +=  0x01<<7;
        }
        sendBuffer[14]=high8Bits;
    }



    if ((sendMsg(sendBuffer,15))!=0)
        return SOCKET_SEND_ERR;

    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    //设置数据长度
    sprintf(formatBuffer,"%d",dataBytesNum);
    if (comboCmdMsg(COMMAND_READ,formatBuffer,10)!= RVP_NO_ERR)//Read Proc data
        return SOCKET_SEND_ERR;

    char sSize[10];
    int iSize,iRecvSize;

    iRecvSize = recv(clientSocket,sSize,8,0);
    if (iRecvSize!=8)
        return SOCKET_RECV_NOT_CMPLT_ERR;
    sSize[8]=0;
    sscanf(sSize,"%d",&iSize);// = strtol(sSize,&sEnd,10);
    if (iSize<=0)
        return SOCKET_RECV_ERR;
    iRecvSize = recv (clientSocket,recvBuffer,iSize,0);
    if ((strncmp(recvBuffer,"Ack",3))!=0)
        return SOCKET_RECV_ERR;
    if (iRecvSize!=iSize)
    {
        int lenn=iSize-iRecvSize;
        iRecvSize = recv (clientSocket,recvBuffer+iRecvSize,lenn,0);
        if (iRecvSize!=lenn)
            return iRecvSize;
        memcpy(outbuff,recvBuffer+4,dataBytesNum);
        return lenn;
    }
    else
        memcpy(outbuff,recvBuffer+4,dataBytesNum);
    return RVP_NO_ERR;
}

int RVP900::GPARM(char* inBuffer,char *outBuffer){
    sendBuffer[0]=0;
    strcat(sendBuffer,GPARM_PREFIX);//构造写命令
    strcat(sendBuffer,COMMAND_SEP);
    strcat(sendBuffer,COMMAND_WRITE);
    sendBuffer[13]=GPARM_L8BIT;
    sendBuffer[14]=GPARM_H8BIT;
    if ((sendMsg(sendBuffer,15))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    if (int s = comboCmdMsg("READ","128",10)==-1)//Read PARAM
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    for (int i=0;i<128;i++)
        inBuffer[i]=recvBuffer[4+i];
    return RVP_NO_ERR;
}
int RVP900::sendMsg(char *buffer,int length)//向RVP900发送数据
{
    if (send(clientSocket,buffer,length,0)!= RVP_NO_ERR)//将buffer指向的length个字符发送到clientSocket
        return SOCKET_SEND_ERR;
    return RVP_NO_ERR;
}




int RVP900::connectRVP(){//连接到RVP900
    struct sockaddr_in adrin,adrins;

    memset (&adrin,0,sizeof(adrin));

    adrin.sin_family = AF_INET;

    adrin.sin_port = htons(RVP900_PORT);

    if ((clientSocket = socket(AF_INET,SOCK_STREAM,0))==-1)
        return SOCKET_CREATE_ERR;
    adrins.sin_family = AF_INET;
    adrins.sin_addr.s_addr = inet_addr("127.0.0.1");
    adrins.sin_port = htons(8000);
    bind(clientSocket,(const sockaddr *)&adrins,sizeof(adrins));

    if (connect(clientSocket,(const sockaddr *)&adrin,sizeof(adrin))==-1)
        return SOCKET_CONN_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;

    if (int s= comboCmdMsg("INFO","ByteOrder=LittleEndian,WillCompress=0,Version=8.04",56)==-1)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
}

int RVP900::readSocketResp(){//读取rvp900响应信息
    char *sEnd;
    char sSize[10];
    int iSize,iRecvSize;
    iRecvSize = recv (clientSocket,sSize,8,0);//接收8个字节到sSize中
    if (iRecvSize<8)
        return SOCKET_RECV_ERR;
    sSize[8]=0;
    iSize = strtol(sSize,&sEnd,10);//将读取的数据转换为10进制数 该十进制数表示返回数据的大小
    if (iSize<=0)
        return RVP_NO_ERR;
    iRecvSize = recv (clientSocket,recvBuffer,iSize,0);//再读取十进制数个大小到recvBuffer中
    if ((strncmp(recvBuffer,"Ack",3))!=0)//比较读取到的数据的前3个字符是否为“Ack”
        return NOT_ACK_ERR;
    if (iRecvSize!=iSize)//若不相等 表明数据未读取完
    {
        int lenn=iSize-iRecvSize;
        iRecvSize = recv (clientSocket,recvBuffer+iRecvSize,lenn,0);//再次读取剩下的数据
        if (iRecvSize!=lenn)
            return SOCKET_RECV_NOT_CMPLT_ERR;//iRecvSize;
        printf("Ack=%d\n",lenn);
    }
    return RVP_NO_ERR;
}

int RVP900::assembleCmdMsg(int length,char *cmd,char *data){//构造发送的指令信息
    int len;
    sprintf(sendBuffer,"%08d",length);//8位字符指示要发送数据的长度
    strcat(sendBuffer,cmd);//发送的指令
    strcat(sendBuffer,data);//发送的数据
    len=COMMAND_PREFIX_LEN+length;//总的长度
    if ((sendMsg(sendBuffer,len))!=0)//发送sendBuffer指向的长度为len的数据
        return SOCKET_SEND_ERR;
    return RVP_NO_ERR;
}
int RVP900::comboCmdMsg(char *cmd,char *data,int length){//构造发送的指令信息
    sprintf(sendBuffer,"%08d",length);//8位字符指示要发送数据的长度
    strcat(sendBuffer,cmd);//发送的指令
    strcat(sendBuffer,COMMAND_SEP);//添加分隔符
    strcat(sendBuffer,data);//发送的数据
    strcat(sendBuffer,COMMAND_SEP);//添加分隔符
    int len=COMMAND_PREFIX_LEN+length;//总的长度
    if ((sendMsg(sendBuffer,len))!=0)//发送sendBuffer指向的长度为len的数据
        return SOCKET_SEND_ERR;
    return RVP_NO_ERR;
}
int RVP900::RVP9Initialize(){
    //采集数据种类 dBz,dBt,dBw,v，默认为Z、T、V、W
    procZDR = false;
    procZ = true;
    procT = true;
    procV = true;
    procW = true;
    procArc = false;
    procKDP = false;

    //采集的数据是否包含 头部TAG，默认为true
    soprmNHD = true;
    //距离量程 distance range,目前仅设置六个距离范围
    disRange = RANGE_10;
    //脉冲重复频率
    setpwfPRF = 300;
    /*数据采集方式 collect mode,有三种Synchronous，
    *free running，time series，默认是time series
    */
    procMode = procSyncModec;
    //脉冲宽度
    pulseWidth = 1;
    //双PRF，脉冲重复比,此处不是真实比率
    procUnfold = procUnfoldNone;
    //多普勒滤波器 doppler filter
    dopFilter = DF_NONE;
    //处理模式 processing mode
    proMode = PPP;
    //脉冲累积数 pulse accummunate
    soprmPulseAcc = 16;
    //Threshold of LOG、SIG、CCOR、SQI,门限值
    soprmLOGThr=0.0,soprmSIGThr=0.0,soprmCCORThr=0.0,soprmSQIThr=0.0;
    //R2使能 r2 enable
    soprmR2Enable = false;
    //距离平均 distance averaging
    lrmskRangeAvg = 0x0;
    //距离分辨率 125m
    resolution = 125;
    //雷达工作波长 λ = 0.032m
    waveLen = 0.032;
    //最大不模糊速度
    Vmax = 2.4;
    //信号质量系数
    soprmSQI = 0.4;
    //socket

    clientSocket = -1;
    isWorking = false;
    //soprm参数初始化设置
    soprm = {
        0x98,0,0,0,0,0,0,0,0,0,//XARG指令操作码即4个可选参数1
        0x2,0,//soprm指令操作码
        0x20,0,0xa6,0x5,0xae,0x7,0x30,0,0x40,0xfe,// input#1 - input#20
        0x5,0,0x22,0,0x92,0x0,0,0x1,0xa,0x2,
        0xaa,0xaa,0x88,0x88,0xa0,0xa0,0xa0,0xa0,0,0,
        0,0,0x40,0x6,0,0,0,0,0x80,0xc
    };
    return 0;
}
//对命令进行必要的初始化
int RVP900::iniCommand(){

}

/*计算最大不模糊速度*/
int RVP900::calculateVmax(){
    Vmax = 0.25 * setpwfPRF * waveLen;
    //2:3
    if(procUnfold2To3 == procUnfold){
        Vmax *= 2;
    }
    else if(procUnfold3To4 == procUnfold){
        Vmax *= 3;
    }
    else if(procUnfold4To5 == procUnfold){
        Vmax *= 4;
    }
    return Vmax;
}
/*计算输出数据中 头数据所占的字节数**/
int RVP900::calHdrBytes(){
    hdrBytesNum = 0;
    if(procArc){//只会以8bit的形式输出
        if(procZ){
            hdrBytesNum += lrmskBinsNum;
        }
        if(procT){
            hdrBytesNum += lrmskBinsNum;
        }
        if(procV){
            hdrBytesNum += lrmskBinsNum;
        }
        if(procW){
            hdrBytesNum += lrmskBinsNum;
        }

    }
    if(procZ){
        hdrBytesNum += lrmskBinsNum;
    }
    if(procT){
        hdrBytesNum += lrmskBinsNum;
    }
    if(procV){
        hdrBytesNum += lrmskBinsNum;
    }
    if(procW){
        hdrBytesNum += lrmskBinsNum;
    }
    if(cfghdrTag){
        hdrBytesNum += 8;
    }
    //其他的头数据……
}

/*get 、  set 方法**/


const char* RVP900::getAntennaBuf() const {
    return antennaBuf;
}

unsigned char RVP900::getAvgDistance() const {
    return avgDistance;
}

void RVP900::setAvgDistance(unsigned char avgDistance) {
    this->avgDistance = avgDistance;
}

double RVP900::getAzimuth() const {
    return azimuth;
}

void RVP900::setAzimuth(double azimuth) {
    this->azimuth = azimuth;
}

int RVP900::getBinsNum() const {
    return binsNum;
}

void RVP900::setBinsNum(int binsNum) {
    this->binsNum = binsNum;
}

float RVP900::getCcorThreshold() const {
    return CCOR_Threshold;
}

void RVP900::setCcorThreshold(float ccorThreshold) {
    CCOR_Threshold = ccorThreshold;
}

bool RVP900::isDataAll() const {
    return dataALL;
}

void RVP900::setDataAll(bool dataAll) {
    dataALL = dataAll;
}

bool RVP900::isDataArcBit() const {
    return procArc;
}

void RVP900::setProArc(bool procArc) {
    this->procArc = procArc;
}

int RVP900::getDataBytesNum() const {
    return dataBytesNum;
}

void RVP900::setDataBytesNum(int dataBytesNum) {
    this->dataBytesNum = dataBytesNum;
}

bool RVP900::isProcKDP() const {
    return procKDP;
}

void RVP900::setProcKDP(bool procKDP) {
    this->procKDP = procKDP;
}

bool RVP900::isProcT() const {
    return procT;
}

void RVP900::setProcT(bool procT) {
    this->ProcT = procT;
}

bool RVP900::isProcT() const {
    return procT;
}

void RVP900::setProcV(bool procV) {
    this->procV = procV;
}

bool RVP900::isProcW() const {
    return procW;
}

void RVP900::setProcW(bool procW) {
    this->procW = procW;
}

bool RVP900::isProcZ() const {
    return procZ;
}

void RVP900::setProcZ(bool procZ) {
    this->procZ = procZ;
}

bool RVP900::isProcZDR() const {
    return procZDR;
}

void RVP900::setProcZDR(bool procZDR) {
    this->procZDR = procZDR;
}

RVP900::enum_disRange getDisRange() const {
    return disRange;
}

void RVP900::setDisRange( enum_disRange disRange) {
    this->disRange = disRange;
}

RVP900::enum_dopFilter RVP900::getDopFilter() const {
    return dopFilter;
}

void RVP900::setDopFilter( enum_dopFilter dopFilter) {
    this->dopFilter = dopFilter;
}

double RVP900::getElevation() const {
    return elevation;
}

void RVP900::setElevation(double elevation) {
    this->elevation = elevation;
}

const unsigned char* RVP900::getElevationBuff() const {
    return elevationBuff;
}

int RVP900::getHdrBytesNum() const {
    return hdrBytesNum;
}

void RVP900::setHdrBytesNum(int hdrBytesNum) {
    this->hdrBytesNum = hdrBytesNum;
}


bool RVP900::isIsWorking() const {
    return isWorking;
}

void RVP900::setIsWorking(bool isWorking) {
    this->isWorking = isWorking;
}

bool RVP900::isSoprmNHD() const {
    return soprmNHD;
}

void RVP900::setSoprmNHD(bool soprmNHD) {
    this->soprmNHD = soprmNHD;
}
int RVP900::getSetpwfPRF() const {
    return setpwfPRF;
}

void RVP900::setSetpwfPRF( int  setpwfPRF) {
    this->PRF = setpwfPRF;
}

RVP900:: enum_proMode RVP900:: getProMode() const {
    return proMode;
}

void RVP900::setProMode( enum_proMode proMode) {
    this->proMode = proMode;
}

int RVP900::getSetpwfPulseWidth() const {
    return setpwfPulseWidth;
}

void RVP900::setSetpwfPulseWidth(int setpwfPulseWidth) {
    this->setpwfPulseWidth = setpwfPulseWidth;
}

int RVP900::getResolution() const {
    return resolution;
}

void RVP900::setResolution(int resolution) {
    this->resolution = resolution;
}

int RVP900::getRf() const {
    return rf;
}

void RVP900::setRf(int rf) {
    this->rf = rf;
}

bool RVP900::isSoprmR2Enable() const {
    return soprmR2Enable;
}

void RVP900::setSoprmR2Enable(bool soprmR2Enable) {
    this->soprmR2Enable = soprmR2Enable;
}

float RVP900::getSoprmSIGThr() const {
    return soprmSIGThr;
}

void RVP900::setSoprmSIGThr(float  soprmSIGThr) {
    this->soprmSIGThr =  soprmSIGThr;
}

float RVP900::getSoprmSQIThr() const {
    return soprmSQIThr;
}

void RVP900::setSoprmSQIThr(float soprmSQIThr) {
    this->soprmSQIThr = soprmSQIThr;
}

const char* RVP900::getTrstatus() const {
    return trstatus;
}

float RVP900::getVmax() const {
    return Vmax;
}

void RVP900::setVmax(float vmax) {
    Vmax = vmax;
}

float RVP900::getWaveLen() const {
    return waveLen;
}

void RVP900::setWaveLen(float waveLen) {
    this->waveLen = waveLen;
}
