/*
*主要用于获取雷达产品
*雷达产品的计算
*/

#ifndef FETCHDATATHREAD_H
#define FETCHDATATHREAD_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"

extern RVP900 rvp9;//rvp9控制对象

class FetchDataThread : public QThread
{
    Q_OBJECT
public:
    explicit FetchDataThread(QObject *parent = 0);
    bool threadFlag;
protected :
    void run();
signals:

public slots:

};

#endif // FETCHDATATHREAD_H
