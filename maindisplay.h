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


class MainDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

signals:

public slots:

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
    void paintVPal(Palette pal[],int palLenth);
    void paintWPal(Palette pal[],int palLenth);
    void paintDBTPal(Palette pal[],int palLenth);
    void paintDBZPal(Palette pal[],int palLenth);

    /*生成颜色库 R，G，B，RG,GB,RB,RGB*/
    int colorBinFactory();
    /*绘制调色板*/
    int paintPal(Palette pal);

    /*绘制扇形*/
    int paintSector(Sector *pSector);

    /*控制扇形的绘制*/
    int paintSectorManager();

    /*绘制数据点*/
    int startPaint(unsigned char *pbuff,Sector *pSector);

    int paintDBZ( );

    int paintDBT( );

    int paintV( );

    int paintW( );
};

#endif // MAINDISPLAY_H













