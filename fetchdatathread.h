/*
*主要用于获取雷达产品
*雷达产品的计算
*/

#ifndef FETCHDATATHREAD_H
#define FETCHDATATHREAD_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"

//extern char outbuff[16000];
extern int Sum,PRF1,PULSE_MARK;
extern char rBuffer[16000];
extern char pBuffer[968];

//暂不需要这些数据
/*
unsigned char binsZDRBuff[1024];//ZDR bins buff
unsigned char binsKDPBuff[1024];//KDP bins buff
unsigned char binsKDPBuff[1024*6];//ARC bins buff
*/
extern unsigned char binsTAGBuff[8];//TAG buff


class FetchDataThread : public QThread
{
    Q_OBJECT
public:
    explicit FetchDataThread(QObject *parent = 0);
    int  flag;
    bool threadFlag;
protected :
    void run();
signals:

public slots:

};

#endif // FETCHDATATHREAD_H
