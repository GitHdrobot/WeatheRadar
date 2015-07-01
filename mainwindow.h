#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QErrorMessage>

#include "fetchdatathread.h"
#include "dialogsetting.h"  //参数设置对话框头文件
#include "dialogsample.h"   //采样设置对话框


#include "headerctrl.h"




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


    QextSerialPort serialPort;//串口控制对象

    DispDevice dispDev;//存放显示设备信息

    FetchDataThread fetchDataThread;//获取数据线程



public slots:
    void  paraSetSlot();
    void  sampleSlot();
    void  dispFourPicSlot();
    void  disp2PicZTSlot();
    void  disp2PicZVSlot();
    void  disp2PicZWSlot();//显示2图槽函数
    void  disp2PicTVSlot();//显示2图槽函数
    void  disp2PicTWSlot();//显示2图槽函数
    void  disp2PicVWSlot();//显示2图槽函数
    void  disp1PicZSlot();//显示1图槽函数
    void  disp1PicTSlot();//显示1图槽函数
    void  disp1PicVSlot();//显示1图槽函数
    void  disp1PicWSlot();//显示1图槽函数






    void closeEvent(QCloseEvent *);


    //getter,setter
public :
    DispDevice getDispDev() const {
        return dispDev;
    }
    QextSerialPort getSerialPort() const {
        return serialPort;
    }

    void setDispDev( DispDevice dispDev) {
        this->dispDev = dispDev;
    }

    void setSerialPort( QextSerialPort serialPort) {
        this->serialPort = serialPort;
    }

public:
    int collectData();
    /* get diaplay info**/
    int getDispInfo();
    //err dialog
    static void errDialog(int errCode);
    //mainwindow slot signal connect
    void slotSignalconnect();

     // display info initialize
    void dispInitiallize();
    //serial port initialize
    void serialPortInitilize();
public slots:
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
    void on_doubleSpinBoxAzimuth_valueChanged(int arg1);
    void on_doubleSpinBoxElevation_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
