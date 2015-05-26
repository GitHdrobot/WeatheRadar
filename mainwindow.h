#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialogsetting.h"  //参数设置对话框头文件
#include "dialogsample.h"   //采样设置对话框


#include "headerctrl.h"
#include "fetchdatathread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static RVP900 rvp9;//rvp9控制对象

    QextSerialPort serialPort;//串口控制对象

    DispDevice dispDev;//存放显示设备信息

    FetchDataThread fetchDataThread;//获取数据线程


public slots:
    void paraSetSlot();//参数设置槽函数
    void dispFourPicSlot();//显示四图槽函数


    //getter,setter
public :
    DispDevice getDispDev() const {
        return dispDev;
    }
    QextSerialPort getSerialPort() const {
        return serialPort;
    }
    static RVP900 getRvp900() {
        return rvp9;
    }

    void setDispDev( DispDevice dispDev) {
        this->dispDev = dispDev;
    }

    void setSerialPort( QextSerialPort serialPort) {
        this->serialPort = serialPort;
    }

public:
    int collectData();

private slots:
    /*处理 打开发射按钮 发出的点击信号*/
    void on_pbtnOpenTransmit_clicked();
    /*处理 关闭发射按钮 发出的点击信号*/
    void on_pbtnCloseTransmit_clicked();
    /*处理 天线扫描按钮 发出的点击信号*/
    void on_pbtnSweep_clicked();
    /*处理 天线停止扫描按钮 发出的点击信号*/
    void on_pbtnStopSweep_clicked();
    void on_pbtnAzimuth_clicked();
    void on_pbtnElevation_clicked();
    void on_pbtnStop_clicked();
    void on_pbtnCollect_clicked();

    void on_comboBoxMode_activated(int index);
    void on_comboBoxLmsk_activated(int index);
    /*RPF 脉冲重复频率 改变*/
    void on_comboBoxPRF_activated(int index);
    /*双脉冲重复比 改变   改变后仍需对PROC命令的8、9位进行设置*/
    void on_comboBoxDPrf_activated(int index);
    /*脉宽  改变*/
    void on_comboBoxPulseWidth_activated(int index);
    void on_comboBoxDopFilter_activated(int index);
    void on_doubleSpinBoxAzimuth_valueChanged(double arg1);
    void on_doubleSpinBoxElevation_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
