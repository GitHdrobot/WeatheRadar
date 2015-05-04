#ifndef PALETTE_H
#define PALETTE_H


class palette
{

public:
    //边框宽度
    int frameWidth;
    //边框颜色
    int rgb_Red,rgb_Green,rgb_Blue;
    //边框位置
    int xloc,yloc;
    //边框大小
    int width,height;
    //填充颜色
    int fillRed,fillGreen,fillBlue;
    //文字说明
    char *comTxt;

public:
    palette();
    ~palette();


    char* getComTxt() const ;
    void setComTxt(char* comTxt);
    int getFillBlue() const ;
    void setFillBlue(int fillBlue) ;
    int getFillGreen() const ;
    void setFillGreen(int fillGreen) ;
    int getFillRed() const ;
    void setFillRed(int fillRed) ;
    int getFrameWidth() const ;
    void setFrameWidth(int frameWidth) ;
    int getHeight() const ;
    void setHeight(int height) ;
    int getRgbBlue() const ;
    void setRgbBlue(int rgbBlue) ;
    int getRgbGreen() const ;
    void setRgbGreen(int rgbGreen) ;
    int getRgbRed() const ;
    void setRgbRed(int rgbRed) ;
    int getWidth() const ;
    void setWidth(int width) ;
    int getXloc() const;
    void setXloc(int xloc) ;
    int getYloc() const ;
    void setYloc(int yloc) ;

};

#endif // PALETTE_H
