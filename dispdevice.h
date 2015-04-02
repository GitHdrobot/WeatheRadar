#ifndef DISPDEVICE_H
#define DISPDEVICE_H

#include <QObject>

class DispDevice : public QObject
{
    Q_OBJECT
public:
    explicit DispDevice(QObject *parent = 0);
    ~DispDevice();

signals:

public slots:
};

#endif // DISPDEVICE_H
