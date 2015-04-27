#include "dispdevice.h"

DispDevice::DispDevice()
{

}

DispDevice::~DispDevice()
{

}

int DispDevice::getResWidth(){
    return resWidth;
}
int DispDevice::getResHeight(){
    return resHeight;
}
int DispDevice::setResWidth(int width){
    this.resWidth = width;
}

int DispDevice::setResHeight(int height){
    this.resHeight = height;
}

int DispDevice::setResWidthHeight(int width,int height){
    this.resHeight = height;
    this.resWidth = width;
}

int DispDevice::getDispAreaWidth(){
    return dispAreaWidth;
}
int DispDevice::getDispAreaHeight(){
    return dispAreaHeight;
}
int DispDevice::setDispAreaWidth(){
    this.dispAreaWidth = widthRatio * resWidth;
}
int DispDevice::setDispAreaHeight(){
    this.dispAreaWidth = hightRatio * resHeight;
}
int DispDevice::setDispAreaWidth(int width){
    this.dispAreaWidth = width;
}

int DispDevice::setDispAreaHeight(int height){
    this.dispAreaHeight = height;
}

int DispDevice::setDispAreaWidthHeight(int width,int height){
    this.dispAreaHeight = height;
    this.dispAreaWidth = width;
}
