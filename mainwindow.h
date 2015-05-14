#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialogsetting.h"  //参数设置对话框头文件
#include "dialogsample.h"   //采样设置对话框


#include "constcode.h"

#include "rvp900.h"

#include "dispdevice.h"

extern DispDevice dispDev;


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


public slots:
    void paraSetSlot();//参数设置槽函数
    void dispFourPicSlot();//显示四图槽函数



//public :
   // void paintEvent(QPaintEvent *);
   // RVP900 rvp900;

private slots:
    void on_pbtnOpenTransmit_clicked();
    void on_pbtnCloseTransmit_clicked();
    void on_pbtnSweep_clicked();
    void on_pbtnStopSweep_clicked();
    void on_pbtnAzimuth_clicked();
    void on_pbtnElevation_clicked();
    void on_pbtnStop_clicked();
    void on_pbtnCollect_clicked();

    void on_comboBoxMode_activated(int index);
    void on_comboBoxLmsk_activated(int index);
    void on_comboBoxPRF_activated(int index);
    void on_comboBoxDPrf_activated(int index);
    void on_comboBoxPulseWidth_activated(int index);
    void on_comboBoxDopFilter_activated(int index);
    void on_doubleSpinBoxAzimuth_valueChanged(double arg1);
    void on_doubleSpinBoxElevation_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
