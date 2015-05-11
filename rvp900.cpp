#include "rvp900.h"



RVP900::RVP900()
{
    clientSocket = -1;
    //pulseRatio = 0x80;

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
        sendBuffer[13+i]=SOPRM[i];
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
    if(hdrTag_BIT){
        inputNBuff += CFGHDR_TAG;
    }
    if(hdrPRT_BIT){
        inputNBuff += CFGHDR_PRT;
    }
    if(hdrPul_BIT){
        inputNBuff += CFGHDR_PUL;
    }
    if(hdrTim_BIT){
        inputNBuff += CFGHDR_TIM;
    }
    if(hdrGpm_BIT){
        inputNBuff += CFGHDR_GPM;
    }
    if(hdrFlg_BIT){
        inputNBuff += CFGHDR_FLG;
    }
    if(hdrUTC_BIT){
        inputNBuff += CFGHDR_UTC;
    }
    sendBuffer[15]=inputNBuff;
    inputNBuff = 0x00;
    if(hdrMMT_BIT){
        inputNBuff += CFGHDR_MMT;
    }
    if(hdrSYT_BIT){
        inputNBuff += CFGHDR_SYT;
    }
    if(hdrPBN_BIT){
        inputNBuff += CFGHDR_PBN;
    }
    if(hdrTID_BIT){
        inputNBuff += CFGHDR_TID;
    }
    sendBuffer[16] = inputNBuff;
    sendBuffer[17] = BYTE_CLEAR;
    sendBuffer[18] = BYTE_CLEAR;

    hdrBytesNum = getHeaderLength();

    if ((sendMsg(sendBuffer,19))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;
    return RVP_NO_ERR;
}
//load range mask
int RVP900::loadRanMsk(int ranMark){
    sendBuffer[0]=0;
    //距离掩码设置的掩码位个数
    int markNums = (ranMark % resolution)?0:(ranMark / resolution + 1);
    strcat (sendBuffer,LRMSK_PREFIX);//OP_LRMSK
    strcat (sendBuffer,COMMAND_WRITE);
    strcat (sendBuffer,COMMAND_SEP);
    sendBuffer[13]=LRMSK_OPCODE; //距离掩码指令操作码
    sendBuffer[14]= avgDistance;    //距离平均
    binsNum = markNums / (avgDistance+1);
    /*要先发一次？？？**/
    if ((sendMsg(sendBuffer,15))!=0)
        return SOCKET_SEND_ERR;
    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;

    sendBuffer[0]=0;
    strcat (sendBuffer,LRMSK_IN_PREFIX);//距离掩码输入参数
    strcat (sendBuffer,COMMAND_WRITE);//写入指令
    strcat (sendBuffer,COMMAND_SEP);//指令参数分隔符
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
    if ((sendMsg(sendBuffer,1037))!=0)//发送信息
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
int RVP900::PROC(char *outBuffer){
    low8Bits = 0x00;
    high8Bits = 0x00;
    sendBuffer[0]=0;
    strcat(sendBuffer,PROC_FREFIX);
    strcat(sendBuffer,COMMAND_WRITE);
    strcat(sendBuffer,COMMAND_SEP);
    low8Bits = PROC_BS_OPCODE;  //PROC command opcode0x06
    //sendBuffer[13]=PROC_L8BIT;
    if(colMode == SYNCHRONOUS){
        low8Bits += PROC_SYNCHRONOUS;
    }else if(colMode == FREE_RUNNING){
        low8Bits += PROC_FREE_RUNNING;
    }else if(colMode == TIME_SERIES){//该模式 未明确
        low8Bits += PROC_SYNCHRONOUS;
    }
    if(dataKDP_BIT){
        low8Bits += PROC_KDP;//KDP第7位
    }
    sendBuffer[13] = low8Bits;

    if(PRF_Ratio == PRF_NONE){//双PRF比率
        high8Bits   +=   PROC_UNFOLD_NONE;
    }else if(PRF_Ratio = PRF_2TO3){
        high8Bits   +=   PROC_UNFOLD_2TO3;
    }else if(PRF_Ratio = PRF_3TO4){
        high8Bits   +=   PROC_UNFOLD_3TO4;
    }else if(PRF_Ratio = PRF_4TO5){
        high8Bits   +=   PROC_UNFOLD_4TO5;
    }
    if(dataALL){
        high8Bits   +=  PROC_W;
        high8Bits   +=  PROC_T;
        high8Bits   +=  PROC_V;
        high8Bits   +=  PROC_Z;
        high8Bits   +=  PROC_ARC;
        high8Bits   +=  PROC_ZDR;
    }else {
        if(dataZ_BIT){
            high8Bits   +=  PROC_Z;
        }
        if(dataT_BIT){
            high8Bits   +=  PROC_T;
        }
        if(dataV_BIT){
            high8Bits   +=  PROC_V;
        }
        if(dataW_BIT){
            high8Bits   +=  PROC_W;
        }
        if(dataARC_BIT){
            high8Bits   +=  PROC_ARC;
        }
        if(dataZDR_BIT){
            high8Bits   +=  PROC_ZDR;
        }
    }

    sendBuffer[14]=high8Bits;

    if ((sendMsg(sendBuffer,15))!=0)
        return SOCKET_SEND_ERR;

    if (readSocketResp()!=0)
        return SOCKET_READ_ERR;

    if (comboCmdMsg(COMMAND_READ,dataBytesNum,10)!= RVP_NO_ERR)//Read Proc data
        return SOCKET_SEND_ERR;

    char sSize[10];
    int iSize,iRecvSize;

    iRecvSize = recv (clientSocket,sSize,8,0);
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
        memcpy(outBuffer,recvBuffer+4,dataBytesNum);
        return lenn;
    }
    else
        memcpy(outBuffer,recvBuffer+4,dataBytesNum);
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
    if(dispDev.dispAreaWidth > dispDev.dispAreaHeight){
        dispDev.radius = dispDev.dispAreaHeight;
    }else{
        dispDev.radius = dispDev.dispAreaWidth;
    }
    if(dispMode == MODE_1PIC){

    }else if(dispMode == MODE_2PIC){
        dispDev.radius /= 2;
    }else if(dispMode == MODE_4PIC){
        dispDev.radius /= 2;
    }
    //采集数据种类 dBz,dBt,dBw,v，默认为Z、T、V、W
    dataZDR_BIT = false;
    dataZ_BIT = true;
    dataT_BIT = true;
    dataV_BIT = true;
    dataW_BIT = true;
    dataALL = false;
    dataARC_BIT = false;
    dataKDP_BIT = false;
    dataTypeNums = 4;
    //采集的数据是否包含 头部TAG，默认为true
    dataHeader = true;
    //距离量程 distance range,目前仅设置六个距离范围
    disRange = RANGE_FIRST;
    //脉冲重复频率
    PRF = PRF_FIRST;
    /*数据采集方式 collect mode,有三种Synchronous，
    *free running，time series，默认是time series
    */
    colMode = SYNCHRONOUS;
    //脉冲宽度
    pulseWidth = 1;
    //双PRF，脉冲重复比,此处不是真实比率
    PRF_Ratio = PRF_NONE;
    //多普勒滤波器 doppler filter
    dopFilter = DF_NONE;
    //处理模式 processing mode
    proMode = PPP;
    //脉冲累积数 pulse accummunate
    //enum enum_pulAccumulate {};
    //Threshold of LOG、SIG、CCOR、SQI,门限值
    LOG_Threshold=0.0,SIG_Threshold=0.0,CCOR_Threshold=0.0,SQI_Threshold=0.0;
    //R2使能 r2 enable
    RTwoEnable = false;
    //距离平均 distance averaging
    avgDistance = 0x0;
    //距离分辨率 125m
    resolution = 125;
    return 0;
}
/*返回数据的头的长度**/
int RVP900::getHeaderLength(){
    int len = 0;
    if(noHeader){
        return 0;
    }
    if(hdrTag_BIT){//tag 头占4个字 八个字节
        len += 4*2;
    }
    if(hdrPRT_BIT){//0xFFFF
        len += 2*2;
    }
    if(hdrPul_BIT){
        inputNBuff += 1*2;
    }
    if(hdrTim_BIT){
        inputNBuff += 1*2;
    }
    if(hdrGpm_BIT){
        inputNBuff += 64*2;
    }
    if(hdrFlg_BIT){
        inputNBuff += 1*2;
    }
    if(hdrUTC_BIT){
        inputNBuff += 3*2;
    }
    sendBuffer[15]=inputNBuff;
    inputNBuff = 0x00;
    if(hdrMMT_BIT){
        inputNBuff += 1*2;
    }
    if(hdrSYT_BIT){
        inputNBuff += 2*2;
    }
    if(hdrPBN_BIT){
        inputNBuff += 1*2;
    }
    if(hdrTID_BIT){
        inputNBuff += 14*2;
    }
    /*
    if(PedINU){
        inputNBuff += 14*2;
    }*/
    return hdrBytesNum = len;
}
int RVP900::getDataLength(){
    return dataBytesNum = hdrBytesNum + binsNum * dataTypeNums ;
}
