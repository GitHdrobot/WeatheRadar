#include "dispdevice.h"

DispDevice::DispDevice()
{

}

DispDevice::~DispDevice()
{

}


int DispDevice::getHeight() const {
    return height;
}

void DispDevice::setHeight(int height) {
    this->height = height;
}

int DispDevice::getHeightPad() const {
    return heightPad;
}

void DispDevice::setHeightPad(int heightPad) {
    this->heightPad = heightPad;
}

int DispDevice:: getWidth() const {
    return width;
}

void DispDevice::setWidth(int width) {
    this->width = width;
}

int DispDevice::getWidthPad() const {
    return widthPad;
}

void DispDevice::setWidthPad(int widthPad) {
    this->widthPad = widthPad;
}



