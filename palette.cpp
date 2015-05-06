#include "palette.h"

Palette::Palette()
{

}

Palette::~Palette()
{

}


char* Palette::getComTxt() const {
    return comTxt;
}

void Palette::setComTxt(char* comTxt) {
    this->comTxt = comTxt;
}

int Palette::getFillBlue() const {
    return fillBlue;
}

void Palette::setFillBlue(int fillBlue) {
    this->fillBlue = fillBlue;
}

int Palette::getFillGreen() const {
    return fillGreen;
}

void Palette::setFillGreen(int fillGreen) {
    this->fillGreen = fillGreen;
}

int Palette::getFillRed() const {
    return fillRed;
}

void Palette::setFillRed(int fillRed) {
    this->fillRed = fillRed;
}

int Palette::getFrameWidth() const {
    return frameWidth;
}

void Palette::setFrameWidth(int frameWidth) {
    this->frameWidth = frameWidth;
}

int Palette::getHeight() const {
    return height;
}

void Palette::setHeight(int height) {
    this->height = height;
}

int Palette::getRgbBlue() const {
    return rgb_Blue;
}

void Palette::setRgbBlue(int rgbBlue) {
    rgb_Blue = rgbBlue;
}

int Palette::getRgbGreen() const {
    return rgb_Green;
}

void Palette::setRgbGreen(int rgbGreen) {
    rgb_Green = rgbGreen;
}

int Palette::getRgbRed() const {
    return rgb_Red;
}

void Palette::setRgbRed(int rgbRed) {
    rgb_Red = rgbRed;
}

int Palette::getWidth() const {
    return width;
}

void Palette::setWidth(int width) {
    this->width = width;
}

int Palette::getXloc() const {
    return xloc;
}

void Palette::setXloc(int xloc) {
    this->xloc = xloc;
}

int Palette::getYloc() const {
    return yloc;
}

void Palette::setYloc(int yloc) {
    this->yloc = yloc;
}
