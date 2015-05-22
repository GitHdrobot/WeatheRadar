#include "fetchdatathread.h"


/*构造函数*/

FetchDataThread::FetchDataThread(QObject *parent) :
    QObject(parent) {
    flag = 0;

    threadFlag = false;
}

void FetchDataThread::run() {
    int i = 0;
    while (threadFlag) {
        rvp9.PROC();
//        if (rvp9.PROC(rvp9.outbuff) == RVP_NO_ERR) {
//            threadFlag = false;
//            break;
//        }
        //header of each ray
        if(rvp9.hdrTag_BIT){
            for(i=0;i<rvp9.hdrBytesNum;i++) {
                rvp9.binsTAGBuff[i] = rvp9.outbuff[i];
            }
        }
        //目前不需要这些数据
        /*
        if(rvp9.hdrPRT_BIT){

        }
        if(rvp9.hdrPul_BIT){

        }
        if(rvp9.hdrTim_BIT){

        }
        if(rvp9.hdrGpm_BIT){

        }
        if(rvp9.hdrFlg_BIT){

        }
        if(rvp9.hdrUTC_BIT){

        }
        if(rvp9.hdrMMT_BIT){

        }
        if(rvp9.hdrSYT_BIT){

        }
        if(rvp9.hdrPBN_BIT){

        }
        if(rvp9.hdrTID_BIT){

        } */

//        for(;i<rvp9.hdrBytesNum + rvp9.binsNum;i++){
//            rvp9.binsWBuff[i] = rvp9.outbuff[i];
//        }
//        for(;i<rvp9.hdrBytesNum + 2*rvp9.binsNum;i++){
//            rvp9.binsVBuff[i] = rvp9.outbuff[i];
//        }
//        for(;rvp9.hdrBytesNum + 3*rvp9.binsNum;i++){
//            rvp9.binsTBuff[i] = rvp9.outbuff[i];
//        }
//        for(;rvp9.hdrBytesNum + 4*rvp9.binsNum;i++){
//            rvp9.binsZBuff[i] = rvp9.outbuff[i];
//        }

        //ZDR 、KDP暂不需要
        /*
        for(;rvp9.hdrBytesNum + 5*rvp9.binsNum;i++){
            binsZDRBuff[i] = outBuff[i];
        }
        for(;rvp9.hdrBytesNum + 6*rvp9.binsNum;i++){
            binsKDPBuff[i] = outBuff[i];
        }
        */
    }




    while(ThreadFlag)
    {
        int c=read_rvp900(rBuffer,808);
        FLAG=-1;
        switch(Sum)
        {
        case 5:
            for(int i=0;i<8;++i)
                pBuffer[i]=rBuffer[i];
            for(int j=0;j<240;++j)
            {
                int J;
                J=j/3;
                pBuffer[8+4*j]=rBuffer[8+4*J];
                pBuffer[9+4*j]=rBuffer[9+4*J];
                pBuffer[10+4*j]=rBuffer[10+4*J];
                pBuffer[11+4*j]=rBuffer[11+4*J];
            }
            break;
        case 10:
            for(int i=0;i<8;++i)
                pBuffer[i]=rBuffer[i];
            for(int j=0;j<240;++j)
            {
                int J;
                J=j*2/3;
                pBuffer[8+4*j]=rBuffer[8+4*J];
                pBuffer[9+4*j]=rBuffer[9+4*J];
                pBuffer[10+4*j]=rBuffer[10+4*J];
                pBuffer[11+4*j]=rBuffer[11+4*J];
            }
            break;
        case 15:
            for(int i=0;i<8;++i)
                pBuffer[i]=rBuffer[i];
            for(int j=0;j<240;++j)
            {
                int J;
                J=j/2;
                pBuffer[8+4*j]=rBuffer[8+4*J];
                pBuffer[9+4*j]=rBuffer[9+4*J];
                pBuffer[10+4*j]=rBuffer[10+4*J];
                pBuffer[11+4*j]=rBuffer[11+4*J];
            }
            break;
        case 25:
        case 75:
        case 150:
            for(int i=0;i<8;++i)
                pBuffer[i]=rBuffer[i];
            for(int j=0;j<240;++j)
            {
                int J;
                J=j*5/6;
                pBuffer[8+4*j]=rBuffer[8+4*J];
                pBuffer[9+4*j]=rBuffer[9+4*J];
                pBuffer[10+4*j]=rBuffer[10+4*J];
                pBuffer[11+4*j]=rBuffer[11+4*J];
            }
            break;
        default:break;
        }
        if(PRF1==500&&PULSE_MARK==20)
        {
            for(int i=952;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==500&&PULSE_MARK==10)
        {
            for(int i=956;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==1000&&PULSE_MARK==20)
        {
            for(int i=936;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==1000&&PULSE_MARK==10)
        {
            for(int i=952;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==3000&&PULSE_MARK==20)
        {
            for(int i=872;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==3000&&PULSE_MARK==10)
        {
            for(int i=920;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==5000&&PULSE_MARK==10)
        {
            for(int i=872;i<968;i++)
                pBuffer[i]=0;
        }
        else if(PRF1==5000&&PULSE_MARK==5)
        {
            for(int i=904;i<968;i++)
                pBuffer[i]=0;
        }
    }





}
