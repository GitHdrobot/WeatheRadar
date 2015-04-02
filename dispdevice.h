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

    int getResWidth();
    int getResHeight();
    int setResWidth(int width);
    int setResHeight(int height);
    int setResWidthHeight(int width,int height);

    int getDispAreaWidth();
    int setDispAreaWidth();
    int getDispAreaHeight();
    int setDispAreaHeight();
};

#endif // DISPDEVICE_H
