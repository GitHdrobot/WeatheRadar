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
