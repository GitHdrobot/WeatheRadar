#include "fetchdatathread.h"

extern RVP900 rvp9;//rvp9控制对象

/*构造函数*/

FetchDataThread::FetchDataThread()
{
    threadFlag = false;
}

void FetchDataThread::run() {
    while (threadFlag) {
        //rvp9.PROC();
        if (rvp9.PROC() != RVP_NO_ERR) {
            threadFlag = false;
            break;
        }
        //取得tag数据
        memcpy(rvp9.binsTAGBuff,rvp9.outbuff,8);
        //取得dBZ数据
        memcpy(rvp9.binsZBuff,rvp9.outbuff+8,rvp9.lrmskBinsNum);
        //取得dBT数据
        memcpy(rvp9.binsTBuff,rvp9.outbuff+rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);
        //取得V数据
        memcpy(rvp9.binsVBuff,rvp9.outbuff+2*rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);
        //取得W数据
        memcpy(rvp9.binsWBuff,rvp9.outbuff+3*rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);
    }
}
