#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <stdio.h>
#include <QTimer>
#include <QDateTime>

#include "constcode.h"

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
    unsigned char PalColorMat[PAL_COLOR_NUM][BASE_COLOR_NUM];     //调色板颜色矩阵256*3
    //绘制调色板V,W,DBT,DBZ
    void paintShadeGuide();
    void paintVPal();
    void paintWPal();
    void paintDBTPal();
    void paintDBZPal();
    void paintPie(int drawMode);
    /*颜色库构造 R、G、B，RG、RB、GB，Y = 3*(x^3 + x),x = 16,Y = 4*k+96
    *RGB的变化范围为0-255，共256个颜色，取16个颜色，隔16取1
    */
    unsigned char colorNums;
    void colorPalFactory();

    QPainter painter;
    void paintEvent(QPaintEvent *);

};

#endif // MAINDISPLAY_H
