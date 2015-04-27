#ifndef DISPDEVICE_H
#define DISPDEVICE_H

class DispDevice
{
public:
    DispDevice();
    ~DispDevice();
public:
    int resWidth;//显示设备宽度
    int resHeight;//显示设备高度

    /*高度约耗7pixel，宽度约365pixel**/
    int dispAreaWidth;//显示区域宽度
    int dispAreaHeight;//显示区域高度

    /*显示的扇形半径**/
    int radius;

    /*显示区域相对于设备宽度的比率 即：dispAreaWidth = resWidth * widthRatio*/
    int widthRatio;
    /*显示区域相对于设备高度的比率 dispAreaHeight = resHeight * widthRatio*/
    int hightRatio;

    int getResWidth();
    int getResHeight();
    int setResWidth(int width);
    int setResHeight(int height);
    int setResWidthHeight(int width,int height);

    int getDispAreaWidth();
    int setDispAreaWidth();
    int getDispAreaHeight();
    int setDispAreaHeight();

    int setDispAreaHeight(int height);
    int setDispAreaWidth(int width);
    int setDispAreaWidthHeight(int width,int height);
};

#endif // DISPDEVICE_H
