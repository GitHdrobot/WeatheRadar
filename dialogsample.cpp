#include "dialogsample.h"
#include "ui_dialogsample.h"

DialogSample::DialogSample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSample)
{
    ui->setupUi(this);
}

DialogSample::~DialogSample()
{
    delete ui;
}
