#ifndef CALIBRATION_H
#define CALIBRATION_H

//刻度对象

class Calibration
{
public:
    Calibration();
    ~Calibration();
    int Red,Green,Blue;//RGB
    int width;
    const char* value;
};

#endif // CALIBRATION_H
