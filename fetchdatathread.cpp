#include "fetchdatathread.h"
#include "rvp900.h"
/*构造函数*/
FetchDataThread::FetchDataThread(QObject *parent) :
    QObject(parent)
{
    flag=0;

    threadFlag=false;
}

void FetchDataThread::run(){
    while(threadFlag)
    {
       int c = rvp9.PROC(inbuff,outbuff);
    }
}
