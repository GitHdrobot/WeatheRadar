#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <stdio.h>
#include <QTimer>
#include <QDateTime>
#include <QDesktopWidget>

#include "headerctrl.h"


extern QRect timeRect,dateRect,freqRect,eleRect,dfreqRatioRect,distanceRect;//save rect of time,date,frequency,elevation

class MainDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

signals:

public slots:

    void on_update_timeout();

public:
    unsigned char PalColorMat[palColorNum][baseColorNum];     //调色板颜色矩阵256*3
    //色标
    Palette dBZPal[palNum],dBTPal[palNum],vPal[palNum],wPal[palNum];
    //扇形
    Sector dBZSector,dBTSector,vSector,wSector;

    int colorNums;

    bool isPalExist;

    QPainter painter;
    void paintEvent(QPaintEvent *);

    //绘制调色板V,W,DBT,DBZ
    void paintShadeGuide();
    void paintVPal(Palette pal[],int palLenth,QPoint slt);
    void paintWPal(Palette pal[],int palLenth,QPoint slt);
    void paintDBTPal(Palette pal[],int palLenth,QPoint slt);
    void paintDBZPal(Palette pal[],int palLenth,QPoint slt);

    /*生成颜色库 R，G，B，RG,GB,RB,RGB*/
    int colorBinFactory();
    /*绘制调色板*/
    int paintPal(Palette pal);

    /*绘制扇形*/
    int paintSector(Sector *pSector);

    /*控制扇形的绘制*/
    int paintManager();

    /*绘制数据点*/
    int startPaint(unsigned char *pbuff,Sector *pSector);

    int paintDBZ( );

    int paintDBT( );

    int paintV( );

    int paintW( );

    /*paint picture title*/
    int paintTitle(QRect rect,const char*p);
    //
    void paintDispInfo();

};

#endif // MAINDISPLAY_H













