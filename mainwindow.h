#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialogsetting.h"  //参数设置对话框头文件
#include "dialogsample.h"   //采样设置对话框


#include "constcode.h"

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



public :
   // void paintEvent(QPaintEvent *);

};

#endif // MAINWINDOW_H