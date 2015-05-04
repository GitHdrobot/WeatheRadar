#ifndef SECTOR_H
#define SECTOR_H


class Sector
{
public:
    Sector();
    ~Sector();
public:
    int xloc,yloc;//X，Y坐标
    int widthi,heighti;//宽、高
    int startAnglei,endAnglei;//起始角度
    int arcCalNumi,arcCalWidthi;//圆弧上刻度的个数,刻度线的宽度
    int radCalNumi,radCalWidthi;//半径上刻度的个数,刻度线的宽度
    //value
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    int arcStaVali,arcValPerScalei,arcSpaceScalei;
    //圆弧刻度上标定的起始刻度的值、每个刻度代表的值,每隔几个刻度标定一次值
    int radStaVali,radValPerScalei,radSpaceScalei;


public :
    setXloc(int x);

    setYloc(int y);


    setWidthi(int w);

    setHeighti(int h);

    setStartAnglei(int sa);

    setEndAnglei(int ea);

    setArcCalNumi(int n);

    setArcCalWidthi(int w);

    setRadCalNumi(int n);

    setRadCalWidthi(int w);


    setArcStaVali(int s);

    setArcValPerScalei(int p);

    setArcSpaceScalei(int scales);


    setRadStaVali(int s);

    setRadValPerScalei(int p);

    setRadSpaceScalei(int scales);


    getXloc( );

    getYloc( );


    getWidthi( );

    getHeighti( );

    getStartAnglei( );

    getEndAnglei( );

    getArcCalNumi( );

    getArcCalWidthi( );

    getRadCalNumi( );

    getRadCalWidthi( );


    getArcStaVali();

    getArcValPerScalei();

    getArcSpaceScalei();


    getRadStaVali();

    getRadValPerScalei();

    getRadSpaceScalei();



};



#endif // SECTOR_H
