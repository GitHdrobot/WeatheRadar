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
        if (rvp9.PROC(rvp9.outbuff) != RVP_NO_ERR) {
            //return SOCKET_READ_ERR;
        }
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
        for(;i<rvp9.hdrBytesNum + rvp9.binsNum;i++){
            rvp9.binsWBuff[i] = rvp9.outbuff[i];
        }
        for(;i<rvp9.hdrBytesNum + 2*rvp9.binsNum;i++){
            rvp9.binsVBuff[i] = rvp9.outbuff[i];
        }
        for(;rvp9.hdrBytesNum + 3*rvp9.binsNum;i++){
            rvp9.binsTBuff[i] = rvp9.outbuff[i];
        }
        for(;rvp9.hdrBytesNum + 4*rvp9.binsNum;i++){
            rvp9.binsZBuff[i] = rvp9.outbuff[i];
        }
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
}
