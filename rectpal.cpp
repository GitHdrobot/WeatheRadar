#include "rectpal.h"

/*矩形调色板 一般15个矩形**/
RectPal::RectPal()
{
    /*矩形调色板刻度 的 文字标识*/
    calText = "0dbm";
    /*矩形调色板的X、Y坐标*/
    posX = 0,posY = 0;
    /*矩形调色板的宽度、高度*/
    width = 0,hight = 0;
    /*边框颜色 填充颜色*/
    frameColor = Qt::white,fillColor = Qt::black;

}

RectPal::~RectPal()
{

}

RectPal::setCalText(char *text){
    calText = *text;
}
char* RectPal::getCalText(){
    return calText;
}
RectPal::setPosX(int x){
    posX = x;
}
int RectPal::getPosX(){
    return posX;
}
RectPal::setPosY(int y){
    posY = y;
}
int RectPal::getPosY(){
    return posY;
}
RectPal::setWidth(int width){
    this->width= width;
}
int RectPal::getWidth(){
    return this->width;
}
RectPal::setHight(int hight){
    this->hight = hight;
}
int RectPal::getHight(){
    return this->hight;
}
RectPal::setFrameColor(Qt::GlobalColor color){
    frameColor = color;
}
Qt::GlobalColor RectPal::getFrameColor(){
    return frameColor;
}
RectPal::setFillColor(Qt::GlobalColor color){
    this->fillColor = color;
}
Qt::GlobalColor RectPal::getFillColor(){
    return this->fillColor;
}
