#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <stdio.h>
#include <QTimer>
#include <QDateTime>
#include <QDesktopWidget>

#include "constcode.h"

#include "palette.h"
#include "sector.h"

/*调用RVP900中的成员函数*/
#include "rvp900.h"


class MainDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

signals:

public slots:

public:
    unsigned char PalColorMat[palColorNum+100][baseColorNum];     //调色板颜色矩阵256*3
    //调色板
    Palette pal[palNum];
    //扇形
    Sector sector;

    /*颜色库构造 R、G、B，Y = x*x*x,x = 16,Y = 16^3
    *RGB的变化范围为0-255，共256个颜色，取16个颜色，隔16取1
    */
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
    void colorPalFactory();
    /*绘制调色板*/
    int paintPal(Palette pal);

    /*绘制扇形*/
    int paintSector();

    /*控制扇形的绘制*/
    int paintSectorManager();
};

#endif // MAINDISPLAY_H













