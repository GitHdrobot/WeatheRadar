#ifndef SECTOR_H
#define SECTOR_H

#include <qobject.h>
#include <qpoint.h>

class Sector
{
public:
    Sector();
    ~Sector();
public:
    int xloc,yloc;//X，Y坐标
    int width,height;//宽、高

    int startAngle,endAngle,spanAngle;//起始角度、跨度
    int rotateAngle;//圆弧上刻度线 旋转的刻度
    int numSystem;//刻度进制 即多少个小刻度组成一个大刻度
    int arcCalNum,arcCalWidth;//圆弧上刻度的个数,刻度线的宽度
    int radCalNum,radCalWidth;//半径上刻度的个数,刻度线的宽度
    //value
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    int arcStartVal,arcValPerScale,arcSpaceScale;
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    int radStartVal,radValPerScale,radSpaceScale;
    //扇形边框颜色
    int rgb_Red,rgb_Blue,rgb_Green;


    QPoint center;

public :

    int getArcCalNum() const ;

    void setArcCalNum(int arcCalNum) ;

    int getArcCalWidth() const ;

    void setArcCalWidth(int arcCalWidth) ;

    int getArcSpaceScale() const ;

    void setArcSpaceScale(int arcSpaceScale) ;

    int getArcStartVal() const ;

    void setArcStartVal(int arcStartVal) ;

    int getArcValPerScale() const ;

    void setArcValPerScale(int arcValPerScale) ;

    int getEndAngle() const ;

    void setEndAngle(int endAngle) ;
    int getHeight() const ;
    void setHeight(int height) ;

    int getRadCalNum() const ;

    void setRadCalNum(int radCalNum) ;

    int getRadCalWidth() const ;

    void setRadCalWidth(int radCalWidth) ;

    int getRadSpaceScale() const ;

    void setRadSpaceScale(int radSpaceScale) ;

    int getRadStartVal() const ;

    void setRadStartVal(int radStartVal) ;

    int getRadValPerScale() const ;

    void setRadValPerScale(int radValPerScale) ;

    int getRgbBlue() const ;

    void setRgbBlue(int rgbBlue) ;
    int getRgbGreen() const ;
    void setRgbGreen(int rgbGreen);

    int getRgbRed() const;

    void setRgbRed(int rgbRed);

    int getStartAngle() const ;

    void setStartAngle(int startAngle) ;

    int getWidth() const ;

    void setWidth(int width) ;

    int getXloc()const ;

    void setXloc(int xloc) ;

    int getYloc() const ;
    void setYloc(int yloc);



    int getSpanAngle() const ;

    void setSpanAngle(int spanAngle) ;


    int getRotateAngle() const;

    void setRotateAngle(int rotateAngle) ;

    int getNumSystem() const ;

    void setNumSystem(int numSystem) ;

    QPoint getCenter() const;

    void setCenter(QPoint center);
    //计算扇形的中心点
    QPoint calculateCenter();
};



#endif // SECTOR_H
