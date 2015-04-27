#ifndef RECTPAL_H
#define RECTPAL_H

#include <qnamespace.h>

class RectPal
{
    //properties
public:
    /*举行调色板刻度 的 文字标识*/
    unsigned char  calText[10];
    /*举行调色板的X、Y坐标*/
    int posX,posY;
    /*矩形调色板的宽度、高度*/
    int width,hight;
    /*边框颜色 填充颜色*/
    Qt::GlobalColor  frameColor,fillColor;
    //methods
public:
    setCalText(char *text);
    char* getCalText();
    setPosX(int x);
    int getPosX();
    setPosY(int y);
    int getPosY();
    setWidth(int width);
    int getWidth();
    setHight(int hight);
    int getHight();
    setFrameColor(Qt::GlobalColor color);
    Qt::GlobalColor getFrameColor();
    setFillColor(Qt::GlobalColor color);
    Qt::GlobalColor getFillColor();
    RectPal();
    ~RectPal();
};

#endif // RECTPAL_H
