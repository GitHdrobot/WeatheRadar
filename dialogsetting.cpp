#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    connect(ui->checkBox3x3,SIGNAL(clicked()),this,SLOT(on_checkBox3x3_clicked()));
    connect(ui->checkBoxCMS,SIGNAL(clicked()),this,SLOT(on_checkBoxCMS_clicked()));
    connect(ui->checkBoxDsr,SIGNAL(clicked()),this,SLOT(on_checkBoxDsr_clicked()));
    connect(ui->checkBoxLsr,SIGNAL(clicked()),this,SLOT(on_checkBoxLsr_clicked()));
    connect(ui->checkBoxR2Enable,SIGNAL(clicked()),this,SLOT(on_checkBoxR2Enable_clicked()));
    connect(ui->checkBoxRangeNorm,SIGNAL(clicked()),this,SLOT(on_checkBoxRangeNorm_clicked()));

    connect(ui->comboBoxBinNum,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxBinNum_currentIndexChanged()));
    connect(ui->comboBoxProcMode,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxProcMode_currentIndexChanged(int)));
    connect(ui->comboBoxPulseAccu,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxPulseAccu_currentIndexChanged(int)));
    connect(ui->comboBoxProcMode,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxProcMode_currentIndexChanged(int)));

    connect(ui->doubleSpinBoxCCORThreshold,SIGNAL(editingFinished()),this,SLOT(on_doubleSpinBoxCCORThreshold_editingFinished()));
    connect(ui->doubleSpinBoxLogThreshold,SIGNAL(editingFinished()),this,SLOT(on_doubleSpinBoxLogThreshold_editingFinished()));
    connect(ui->doubleSpinBoxSigThreshold,SIGNAL(editingFinished()),this,SLOT(on_doubleSpinBoxSigThreshold_editingFinished()));
    connect(ui->doubleSpinBoxSQIThreshold,SIGNAL(editingFinished()),this,SLOT(on_doubleSpinBoxSQIThreshold_editingFinished()));

    connect(ui->pbtnApply,SIGNAL(clicked()),this,SLOT(on_pbtnApply_clicked()));

}

DialogSetting::~DialogSetting()
{
    delete ui;
}
//处理模式
void DialogSetting::on_comboBoxProcMode_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:  rvp9.soprm[29]=0x0;break;
    case 1:  rvp9.soprm[29]=0x01;break;
    case 2:  rvp9.soprm[29]=0x02;break;
    case 3:  rvp9.soprm[29]=0x04;break;
    case 4:  rvp9.soprm[29]=0x05;break;
    default: break;
    }

}

void DialogSetting::on_comboBoxPulseAccu_currentIndexChanged(int index)
{
    //脉冲累积数 0:16,1:32,2:64……
    switch(index)
    {
    case 0:  rvp9.soprm[12]=0x10;rvp9.soprm[13]=0; break;
    case 1:  rvp9.soprm[12]=0x20;rvp9.soprm[13]=0; break;
    case 2:  rvp9.soprm[12]=0x40;rvp9.soprm[13]=0; break;
    case 3:  rvp9.soprm[12]=0x80;rvp9.soprm[13]=0; break;
    case 4:  rvp9.soprm[12]=0x00;rvp9.soprm[13]=0x01; break;
    case 5:  rvp9.soprm[12]=0x00;rvp9.soprm[13]=0x02; break;
    case 6:  rvp9.soprm[12]=0x00;rvp9.soprm[13]=0x04; break;
    default: break;
    }
}

void DialogSetting::on_comboBoxWinType_currentIndexChanged(int index)
{
    //0:Rectangular, 1:Hamming, 2:Blackman, 3:Exact,Blackman, 4:VonHann.
    switch(index)
    {
    case 0:  rvp9.soprm[31]=0X0;  break;
    case 1:  rvp9.soprm[31]=0X02; break;
    case 2:  rvp9.soprm[31]=0X04; break;
    case 3:  rvp9.soprm[31]=0X06; break;
    case 4:  rvp9.soprm[31]=0X08; break;
    default: break;
    }
}

void DialogSetting::on_comboBoxBinNum_currentIndexChanged(int index)
{
    if(0 == index){
        rvp9.lrmskBinsNum = 125;
    }
}
//距离订正通断
void DialogSetting::on_checkBoxRangeNorm_clicked()
{
    if(ui->checkBoxRangeNorm->isChecked())
    {
        rvp9.soprm[14]=rvp9.soprm[14]|1;
    }
    else
    {
        rvp9.soprm[14]=rvp9.soprm[14]&254;
    }
}
//R2使能
void DialogSetting::on_checkBoxR2Enable_clicked()
{
    if(ui->checkBoxR2Enable->isChecked())
    {
        rvp9.soprm[14]=rvp9.soprm[14]|128;
    }
    else
    {
        rvp9.soprm[14]=rvp9.soprm[14]&127;
    }
}

//单库杂波消除
void DialogSetting::on_checkBoxCMS_clicked()
{
    if(ui->checkBoxCMS->isChecked())
    {
        rvp9.soprm[15]=(rvp9.soprm[15]|1);
    }
    else
    {
        rvp9.soprm[15]=rvp9.soprm[15]&254;
    }
}
//强度斑点消除
void DialogSetting::on_checkBoxLsr_clicked()
{
    if(Lsr->isChecked())
    {
        rvp9.soprm[14]=rvp9.soprm[14]|4;
    }
    else
    {
        rvp9.soprm[14]=rvp9.soprm[14]&251;
    }
}
//速度斑点消除
void DialogSetting::on_checkBoxDsr_clicked()
{
    if(ui->checkBoxDsr->isChecked())
    {
        rvp9.soprm[14]=rvp9.soprm[14]|2;
    }
    else
    {
        rvp9.soprm[14]=rvp9.soprm[14]&253;
    }
}
//3x3平滑输出
void DialogSetting::on_checkBox3x3_clicked()
{
    if(ui->checkBox3x3->isChecked())
    {
        rvp9.soprm[14]=rvp9.soprm[14]|32;
    }
    else
    {
        rvp9.soprm[14]=rvp9.soprm[14]&223;
    }
}

void DialogSetting::on_doubleSpinBoxLogThreshold_editingFinished()
{
    float logThresh = ui->doubleSpinBoxLogThreshold->value();
    int logThreshi;
    //临时变量 将浮点数转换为二进制数的中间变量
    unsigned short tmps;
    unsigned char stmp[2];
    if(logThresh>=0)
    {
        logThreshi=logThresh*16.0;
        logThreshi=logThresh;
        rvp9.soprm[18]=logThreshi%256;
        rvp9.soprm[19]=logThreshi/256;
    }
    else
    {
        logThresh=logThresh*16.0;
        logThreshi=abs(logThresh);
        stmp[0]=logThreshi%256;
        stmp[1]=logThreshi/256;
        tmps=0xffff-(stmp[0]+stmp[1]*256)+1;
        rvp9.soprm[18]=tmps&0x00ff;
        rvp9.soprm[19]=tmps>>8;

    }
}

//SIG Threashold
void DialogSetting::on_doubleSpinBoxSigThreshold_editingFinished()
{
    float sigThresh = ui->doubleSpinBoxSigThreshold->value();
    int sigThreshi;
    //临时变量 将浮点数转换为二进制数的中间变量
    unsigned short tmps;
    unsigned char stmp[2];
    if(sigThresh>=0)
    {
        sigThreshi=sigThresh*16.0;
        sigThreshi=sigThresh;
        rvp9.soprm[24]=sigThreshi%256;
        rvp9.soprm[25]=sigThreshi/256;
    }
    else
    {
        sigThresh=sigThresh*16.0;
        sigThreshi=abs(sigThresh);
        stmp[0]=sigThreshi%256;
        stmp[1]=sigThreshi/256;
        tmps=0xffff-(stmp[0]+stmp[1]*256)+1;
        rvp9.soprm[24]=tmps&0x00ff;
        rvp9.soprm[25]=tmps>>8;

    }
}

void DialogSetting::on_doubleSpinBoxCCORThreshold_editingFinished()
{
    float ccorThresh = ui->doubleSpinBoxCCORThreshold->value();
    int ccorThreshi;
    //临时变量 将浮点数转换为二进制数的中间变量
    unsigned short tmps;
    unsigned char stmp[2];
    if(sigThresh>=0)
    {
        ccorThreshi=ccorThresh*16.0;
        ccorThreshi=ccorThresh;
        rvp9.soprm[20]=ccorThreshi%256;
        rvp9.soprm[21]=ccorThreshi/256;
    }
    else
    {
        ccorThresh=ccorThresh*16.0;
        ccorThreshi=abs(ccorThresh);
        stmp[0]=ccorThreshi%256;
        stmp[1]=ccorThreshi/256;
        tmps=0xffff-(stmp[0]+stmp[1]*256)+1;
        rvp9.soprm[20]=tmps&0x00ff;
        rvp9.soprm[21]=tmps>>8;

    }
}

void DialogSetting::on_doubleSpinBoxSQIThreshold_editingFinished()
{
    float sqiThresh = ui->doubleSpinBoxCCORThreshold->value();
    sqiThresh=sqiThresh*256;
    int sqiThreshi;
    sqiThreshi=sqiThresh;
    rvp9.soprm[22]=sqiThreshi;
}

void DialogSetting::on_pbtnApply_clicked()
{
      rvp9.setOperPRM();
}
