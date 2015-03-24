/*
*主要用于获取雷达产品
*雷达产品的计算
*/

#ifndef FETCHDATATHREAD_H
#define FETCHDATATHREAD_H

#include <QObject>

extern int Sum,PRF1,PULSE_MARK;
extern char rBuffer[16000];
extern char pBuffer[968];

extern RVP900 *pRVP900;

class FetchDataThread : public QObject
{
    Q_OBJECT
public:
    explicit FetchDataThread(QObject *parent = 0);
    int flag;
    bool threadFlag;
protected :
    void run();
signals:

public slots:

};

#endif // FETCHDATATHREAD_H
