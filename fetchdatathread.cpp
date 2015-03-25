#include "fetchdatathread.h"

/*构造函数*/
FetchDataThread::FetchDataThread(QObject *parent) :
    QObject(parent)
{
    FLAG=0;

    ThreadFlag=false;
}

void FetchDataThread::run(){
    while(ThreadFlag)
    {
        int c=pRVP900.PROC(null,808);
    }
}
