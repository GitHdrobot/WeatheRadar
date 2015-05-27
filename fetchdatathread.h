/*
*主要用于获取雷达产品
*雷达产品的计算
*/

#ifndef FETCHDATATHREAD_H
#define FETCHDATATHREAD_H

#include <QThread>
#include <stdio.h>
#include "rvp900.h"


class FetchDataThread : public QThread
{

public:
    FetchDataThread();
    bool threadFlag;
    void run();


};

#endif // FETCHDATATHREAD_H
