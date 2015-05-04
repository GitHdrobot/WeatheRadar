#ifndef DISPDEVICE_H
#define DISPDEVICE_H

class DispDevice
{
public:
    DispDevice();
    ~DispDevice();
public:
    //设备的宽度、高度
    int width,height;
    //宽高度填充，有效高度，即设备的分辨率减去填充的 为实际可见的
    int widthPad,heightPad;
    int getHeight() const ;

    void setHeight(int height) ;

    int getHeightPad() const ;

    void setHeightPad(int heightPad);

    int getWidth() const ;

    void setWidth(int width);

    int getWidthPad() const ;
    void setWidthPad(int widthPad);
};

#endif // DISPDEVICE_H
