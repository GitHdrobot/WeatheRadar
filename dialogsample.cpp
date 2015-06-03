#include "dialogsample.h"
#include "ui_dialogsample.h"

DialogSample::DialogSample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSample)
{
    ui->setupUi(this);
    connect(ui->dSpinBoxdBZCali,SIGNAL(clicked()),this,SLOT(on_dSpinBoxdBZCali_editingFinished()));
    connect(ui->dSpinBoxNoiseSet,SIGNAL(clicked()),this,SLOT(on_pushButtonNoiseSet_clicked()));
}

DialogSample::~DialogSample()
{
    delete ui;
}

//The alibration reflectivity is referenced to 1.0 kilometers

void DialogSample::on_dSpinBoxdBZCali_editingFinished()
{

    //dbz校准
    float dbz;
    int i_dbz;
    unsigned short s_dbz;
    unsigned char c_dbz[2];
    dbz = ui->dSpinBoxdBZCali->value();
    dbz=dbz*16.0;
    if(dbz>=0)
    {
        i_dbz=dbz;
        rvp9.soprm[26]=(i_dbz%256);
        rvp9.soprm[27]=(i_dbz/256);
    }
    else
    {
        i_dbz=abs(dbz);
        c_dbz[0]=i_dbz%256;
        c_dbz[1]=i_dbz/256;
        s_dbz=0xffff-(c_dbz[0]+c_dbz[1]*256)+1;
        rvp9.soprm[26]=(s_dbz&0x00ff);
        rvp9.soprm[27]=(s_dbz>>8);
    }
    rvp9.setOperPRM();
}

void DialogSample::on_pushButtonNoiseSet_clicked()
{
    if ((rvp9.sampleNoise())!=0)
        return;
    int a=rvp9.GPARM();
    if(a!=0)
        return;
    //unsigned short noise;
    short noise;
    float f_noise;
    noise=(((unsigned char)rvp9.statusBuff[10]+(unsigned char)rvp9.statusBuff[11]*256));
    //??????
    f_noise=6.0+0.03*(float(noise)/4.0-3584.0);
    ui->dSpinBoxNoiseSet->setValue(f_noise);

}
