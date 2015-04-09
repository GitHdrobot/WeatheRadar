#include "maindisplay.h"


MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent)
{
    colorNums = 32;
    colorPalFactory();
    //    FILE *fp;
    //    if((fp=fopen("Palette.dat","rb")))
    //    {
    //        printf("打开调色板成功\n");
    //        fread(PalColorMat,1,768,fp);
    //        fclose(fp);
    //    }
}

MainDisplay::~MainDisplay()
{

}

void MainDisplay::paintEvent(QPaintEvent *){
    painter.begin(this);
    setAutoFillBackground(true);
    paintShadeGuide();
    paintPie(MODE3_1_DBZ);
}

void MainDisplay::paintPie( int drawMode)
{
    painter.save();
    if(drawMode == MODE3_1_DBZ){
        QRectF pieRect(MODE1_ARC_X,MODE1_ARC_Y,MODE1_ARC_W,MODE1_ARC_H);

        painter.setPen(Qt::red);
        painter.save();

        painter.drawPie(pieRect,MODE1_ARC_ST_ANGLE,MODE1_ARC_SP_ANGLE);

        for(int i=1;i<ARC_NUM;i++){
            int x,y,w;
            x = MODE1_ARC_X + i * MODE1_ARC_W / ARC_NUM / 2;
            y = MODE1_ARC_Y + i * MODE1_ARC_W / ARC_NUM / 2;
            w = MODE1_ARC_W - i * MODE1_ARC_W / ARC_NUM;
            painter.drawArc(x,y,w,w,MODE1_ARC_ST_ANGLE,MODE1_ARC_SP_ANGLE);
        }

        //painter.setRenderHint(QPainter::Antialiasing, true);//open Antialiasing
        painter.translate(MODE1_ARC_X+0.5*MODE1_ARC_W,0.5*MODE1_ARC_H+MODE1_ARC_Y);
        painter.rotate(ROTATE_ANGLE);
        for(int i=0;i<3;i++){
            painter.rotate(ROTATE_ANGLE);
            painter.drawLine(0,0,-0.5*MODE1_ARC_W,0);
        }
        painter.restore();
        painter.translate(MODE1_ARC_X+0.5*MODE1_ARC_W,0.5*MODE1_ARC_H+MODE1_ARC_Y);//translate to center of pie
        painter.rotate(ROTATE_ANGLE);
        for(int i=0;i<GRADUATION_NUM;i++){
            painter.rotate(MIN_GRADUATION);
            painter.drawLine(-0.5*MODE1_ARC_W,0,-0.5*MODE1_ARC_W+GRADUATION_LEN,0);
        }
        painter.restore();
    }
}


void MainDisplay::paintShadeGuide() {
    painter.save();
    paintDBZPal();
    //paintDBTPal();
    // paintWPal();
    //paintVPal();
    painter.restore();
}

void  MainDisplay::paintDBZPal(){
    QPen  pen;
    for(int i=1;i<=15;i++)
    {
        int c =i*17;
        pen.setColor(QColor(255,255,255));
        QBrush brush(QColor(PalColorMat[c][0],PalColorMat[c][1],PalColorMat[c][2]));
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(DBZ_PAL_X,DBZ_PAL_Y+i*DBZ_PAL_H,DBZ_PAL_W,DBZ_PAL_H);
    }

}
void MainDisplay::paintDBTPal(){
    QPen  pen;
    for(int i=1;i<=15;i++)
    {
        int c =i*17;
        pen.setColor(QColor(255,255,255));
        QBrush brush(QColor(PalColorMat[c][0],PalColorMat[c][1],PalColorMat[c][2]));
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(DBT_PAL_X,DBT_PAL_Y+i*DBT_PAL_H,DBT_PAL_W,DBT_PAL_H);
    }
}
void  MainDisplay::paintWPal(){
    QPen  pen;
    for(int i=1;i<=15;i++)
    {
        int c =i*17;
        pen.setColor(QColor(255,255,255));
        QBrush brush(QColor(PalColorMat[c][0],PalColorMat[c][1],PalColorMat[c][2]));
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(W_PAL_X,i*W_PAL_H+W_PAL_Y,W_PAL_W,W_PAL_H);
    }
}
void  MainDisplay::paintVPal(){
    QPen  pen;
    for(int i=1;i<=15;i++)
    {
        int c =i*17;
        pen.setColor(QColor(255,255,255));
        QBrush brush(QColor(PalColorMat[c][0],PalColorMat[c][1],PalColorMat[c][2]));
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(V_PAL_X,i*V_PAL_H+V_PAL_Y,V_PAL_W,V_PAL_H);
    }

}

void MainDisplay::colorPalFactory(){
    unsigned char space = 256 / colorNums;
    int cursor = 0;
    //R  0 - colorNums
    for(int i=0;i<colorNums;i++){
        PalColorMat[i][0] = i * space;
        PalColorMat[i][1] = 0;
        PalColorMat[i][2] = 0;
    }
    //cursor = colorNums;
    //G  colorNums - 2 * colorNums
    for(int i=0;i<colorNums;i++){
        PalColorMat[colorNums + i][0] = 0;
        PalColorMat[colorNums + i][1] = space * i;
        PalColorMat[colorNums + i][2] = 0;
    }
    //cursor = 2 * colorNums;
    //B  2*colorNums - 3*colorNums
    for(int i=0;i<colorNums;i++){
        PalColorMat[colorNums*2+i][0] = 0;
        PalColorMat[colorNums*2+i][1] = 0;
        PalColorMat[colorNums*2+i][2] = space * i;
    }
    //cursor = 3 * colorNums;
    //RG
    for(int i=0,k=0;i<colorNums * colorNums;i++,k++){
         for(int j=0;j<colorNums;j++){
             PalColorMat[colorNums*3+ i*colorNums + j][0] = PalColorMat[k][0];
             PalColorMat[colorNums*3+ i][1] = PalColorMat[colorNums + j][1];
         }
    }

    for(int i=0;i<21;i++){//g1
        PalColorMat[21*4 + i][0] = 0;
        PalColorMat[21*4 + i][1] = 128 + i;
        PalColorMat[21*4 + i][2] = 0;
    }
    for(int i=0;i<21;i++){//g2
        PalColorMat[21*5 + i][0] = 0;
        PalColorMat[21*5 + i][1] = 235 + i;
        PalColorMat[21*5 + i][2] = 0;
    }
    for(int i=0;i<21;i++){//g1b1
        PalColorMat[21*6 + i][0] = 0;
        PalColorMat[21*6 + i][1] = 128 + i;
        PalColorMat[21*6 + i][2] = 128 + i;
    }
    for(int i=0;i<21;i++){//g2b2
        PalColorMat[21*7 + i][0] = 0;
        PalColorMat[21*7 + i][1] = 235 + i;
        PalColorMat[21*7 + i][2] = 235 + i;
    }

    for(int i=0;i<21;i++){//b1
        PalColorMat[21*8 + i][0] = 0;
        PalColorMat[21*8 + i][1] = 0;
        PalColorMat[21*8 + i][2] = 128 + i;
    }
    for(int i=0;i<21;i++){//b2
        PalColorMat[21*9 + i][0] = 0;
        PalColorMat[21*9 + i][1] = 0;
        PalColorMat[21*9 + i][2] = 235 + i;
    }
    for(int i=0;i<21;i++){//r1b1
        PalColorMat[21*10 + i][0] = 128 + i;
        PalColorMat[21*10 + i][1] = 0;
        PalColorMat[21*10 + i][2] = 128 + i;
    }
    for(int i=0;i<21;i++){//r2b2
        PalColorMat[21*11 + i][0] = 235 + i;
        PalColorMat[21*11 + i][1] = 0;
        PalColorMat[21*11 + i][2] = 235 + i;
    }
    PalColorMat[252][0] = 0;
    PalColorMat[252][1]= 0;
    PalColorMat[252][2]= 0;

    PalColorMat[253][0] = 200;
    PalColorMat[253][0]= 200;
    PalColorMat[253][0]= 0;

    PalColorMat[255][0] = 255;
    PalColorMat[255][0]= 255;
    PalColorMat[255][0]= 255;

    PalColorMat[254][0]= 128;
    PalColorMat[254][0]= 128;
    PalColorMat[254][0]= 128;
}
