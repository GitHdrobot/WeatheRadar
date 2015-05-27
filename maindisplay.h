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
    //调色板
    Palette pal[palNum];
    //扇形
    Sector sector;

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
    /*该方法生成的颜色不便于选取*/
    /*颜色库构造 R、G、B，Y = x*x*x,x = 16,Y = 16^3
    *RGB的变化范围为0-255，共256个颜色，取16个颜色，隔16取1
    */
    void colorPalFactory();
    /*生成颜色库 Y = 3*x*x + 6*6*6 +16*3 ,x=16,RG,GB,RB,RGB*/
    int colorBinFactory();
    /*绘制调色板*/
    int paintPal(Palette pal);

    /*绘制扇形*/
    int paintSector();

    /*控制扇形的绘制*/
    int paintSectorManager();
};

#endif // MAINDISPLAY_H













