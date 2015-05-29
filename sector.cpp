#include "sector.h"

Sector::Sector() {
    // TODO Auto-generated constructor stub
    //X，Y坐标
    xloc = 0;
    yloc = 0;
    //宽、高
    width = 0;
    height=0;
    //起始角度、跨度
    startAngle = 30;
    endAngle = 150;
    spanAngle = 120;
    //圆弧上刻度线 旋转的刻度
    rotateAngle = 1;
    //刻度进制 即多少个小刻度组成一个大刻度
    numSystem = 30;
    //圆弧上刻度的个数,刻度线的宽度
    arcCalNum = 120;
    arcCalWidth = 5;
    //半径上刻度的个数,刻度线的宽度
    radCalNum = 3;
    radCalWidth = 5;//直接绘制的圆弧 故此变量未使用
    //value
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    arcStartVal = 0;
    arcValPerScale = 1;
    arcSpaceScale = 10;//暂未使用
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    radStartVal = 0;
    radValPerScale = 1;
    radSpaceScale = 10;//暂未使用
    //扇形边框颜色
    rgb_Red = 255;
    rgb_Blue = 255;
    rgb_Green = 255;

}

Sector::~Sector() {
    // TODO Auto-generated destructor stub
}

int Sector::getArcCalNum() const {
    return arcCalNum;
}

void Sector::setArcCalNum(int arcCalNum) {
    this->arcCalNum = arcCalNum;
}

int Sector::getArcCalWidth() const {
    return arcCalWidth;
}

void Sector::setArcCalWidth(int arcCalWidth) {
    this->arcCalWidth = arcCalWidth;
}

int Sector::getArcSpaceScale() const {
    return arcSpaceScale;
}

void Sector::setArcSpaceScale(int arcSpaceScale) {
    this->arcSpaceScale = arcSpaceScale;
}

int Sector::getArcStartVal() const {
    return arcStartVal;
}

void Sector::setArcStartVal(int arcStartVal) {
    this->arcStartVal = arcStartVal;
}

int Sector::getArcValPerScale() const {
    return arcValPerScale;
}

void Sector::setArcValPerScale(int arcValPerScale) {
    this->arcValPerScale = arcValPerScale;
}

int Sector::getEndAngle() const {
    return endAngle;
}

void Sector::setEndAngle(int endAngle) {
    this->endAngle = endAngle;
}

int Sector::getHeight() const {
    return height;
}

void Sector::setHeight(int height) {
    this->height = height;
}

int Sector::getRadCalNum() const {
    return radCalNum;
}

void Sector::setRadCalNum(int radCalNum) {
    this->radCalNum = radCalNum;
}

int Sector::getRadCalWidth() const {
    return radCalWidth;
}

void Sector::setRadCalWidth(int radCalWidth) {
    this->radCalWidth = radCalWidth;
}

int Sector::getRadSpaceScale() const {
    return radSpaceScale;
}

void Sector::setRadSpaceScale(int radSpaceScale) {
    this->radSpaceScale = radSpaceScale;
}

int Sector::getRadStartVal() const {
    return radStartVal;
}

void Sector::setRadStartVal(int radStartVal) {
    this->radStartVal = radStartVal;
}

int Sector::getRadValPerScale() const {
    return radValPerScale;
}

void Sector::setRadValPerScale(int radValPerScale) {
    this->radValPerScale = radValPerScale;
}

int Sector::getRgbBlue() const {
    return rgb_Blue;
}

void Sector::setRgbBlue(int rgbBlue) {
    rgb_Blue = rgbBlue;
}

int Sector::getRgbGreen() const {
    return rgb_Green;
}

void Sector::setRgbGreen(int rgbGreen) {
    rgb_Green = rgbGreen;
}

int Sector::getRgbRed() const {
    return rgb_Red;
}

void Sector::setRgbRed(int rgbRed) {
    rgb_Red = rgbRed;
}

int Sector::getStartAngle() const {
    return startAngle;
}

void Sector::setStartAngle(int startAngle) {
    this->startAngle = startAngle;
}

int Sector::getWidth() const {
    return width;
}

void Sector::setWidth(int width) {
    this->width = width;
}

int Sector::getXloc() const {
    return xloc;
}

void Sector::setXloc(int xloc) {
    this->xloc = xloc;
}

int Sector::getYloc() const {
    return yloc;
}

void Sector::setYloc(int yloc) {
    this->yloc = yloc;
}

int Sector::getSpanAngle() const {
    return spanAngle;
}

void Sector::setSpanAngle(int spanAngle) {
    this->spanAngle = spanAngle;
}

int Sector::getRotateAngle() const {
    return rotateAngle;
}

void Sector::setRotateAngle(int rotateAngle) {
    this->rotateAngle = rotateAngle;
}
int Sector::getNumSystem() const {
    return numSystem;
}

void Sector::setNumSystem(int numSystem) {
    this->numSystem = numSystem;
}


QPoint Sector::getCenter() const{
    return center ;
}

void Sector:: setCenter(QPoint center){
    this->center = center;
}

QPoint Sector::calculateCenter(){
    QPoint p ;
    p.setX(xloc + width / 2);
    p.setY(yloc + height / 2);
    this->setCenter(p);
    return center;
}
