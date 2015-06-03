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
        int i=0;
        if (rvp9.PROC() != RVP_NO_ERR) {
            threadFlag = false;
            break;
        }
        //取得tag数据
        memcpy(rvp9.binsTAGBuff,rvp9.outbuff,8);
//        //取得dBZ数据
//        memcpy(rvp9.binsZBuff,rvp9.outbuff+8,rvp9.lrmskBinsNum);
//        //取得dBT数据
//        memcpy(rvp9.binsTBuff,rvp9.outbuff+rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);
//        //取得V数据
//        memcpy(rvp9.binsVBuff,rvp9.outbuff+2*rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);
//        //取得W数据
//        memcpy(rvp9.binsWBuff,rvp9.outbuff+3*rvp9.lrmskBinsNum+8,rvp9.lrmskBinsNum);

        //计算出平均每个像素占多少个库
        float numPerPixl = rvp9.lrmskBinsNum / sectorWidth;
        int inumPerPixl = numPerPixl;
        //将数据均分到显示区域中
        for(i=0;i< sectorWidth;i++){
            rvp9.binsZBuff[i] = rvp9.outbuff[8+i*inumPerPixl];
        }
        for(i=0;i< sectorWidth;i++){
            rvp9.binsTBuff[i] = rvp9.outbuff[8+rvp9.lrmskBinsNum+i*inumPerPixl];
        }
        for(i=0;i< sectorWidth;i++){
            rvp9.binsVBuff[i] = rvp9.outbuff[8+2*rvp9.lrmskBinsNum+i*inumPerPixl];
        }
        for(i=0;i< sectorWidth;i++){
            rvp9.binsWBuff[i] = rvp9.outbuff[8+3*rvp9.lrmskBinsNum+i*inumPerPixl];
        }
    }
}
