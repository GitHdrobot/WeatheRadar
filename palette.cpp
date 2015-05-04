#include "palette.h"

palette::palette()
{

}

palette::~palette()
{

}


char* palette::getComTxt() const {
    return comTxt;
}

void palette::setComTxt(char* comTxt) {
    this->comTxt = comTxt;
}

int palette::getFillBlue() const {
    return fillBlue;
}

void palette::setFillBlue(int fillBlue) {
    this->fillBlue = fillBlue;
}

int palette::getFillGreen() const {
    return fillGreen;
}

void palette::setFillGreen(int fillGreen) {
    this->fillGreen = fillGreen;
}

int palette::getFillRed() const {
    return fillRed;
}

void palette::setFillRed(int fillRed) {
    this->fillRed = fillRed;
}

int palette::getFrameWidth() const {
    return frameWidth;
}

void palette::setFrameWidth(int frameWidth) {
    this->frameWidth = frameWidth;
}

int palette::getHeight() const {
    return height;
}

void palette::setHeight(int height) {
    this->height = height;
}

int palette::getRgbBlue() const {
    return rgb_Blue;
}

void palette::setRgbBlue(int rgbBlue) {
    rgb_Blue = rgbBlue;
}

int palette::getRgbGreen() const {
    return rgb_Green;
}

void palette::setRgbGreen(int rgbGreen) {
    rgb_Green = rgbGreen;
}

int palette::getRgbRed() const {
    return rgb_Red;
}

void palette::setRgbRed(int rgbRed) {
    rgb_Red = rgbRed;
}

int palette::getWidth() const {
    return width;
}

void palette::setWidth(int width) {
    this->width = width;
}

int palette::getXloc() const {
    return xloc;
}

void palette::setXloc(int xloc) {
    this->xloc = xloc;
}

int palette::getYloc() const {
    return yloc;
}

void palette::setYloc(int yloc) {
    this->yloc = yloc;
}
