#include "maindisplay.h"


MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent)
{
    isPalExist = false;
    colorNums = 16;
    colorPalFactory();
    /*读取配置文件 文件打开成功 **/
    FILE *fp;
    if((fp=fopen("Palette.dat","rb")))
    {
        //printf("打开调色板成功\n");
        fread(PalColorMat,1,colorNums*colorNums*colorNums+BASE_COLOR_NUM*colorNums,fp);
        fclose(fp);
        isPalExist = true;
    }
    if(!isPalExist){
        colorPalFactory();
        fwrite(PalColorMat,1,colorNums*colorNums*colorNums+BASE_COLOR_NUM*colorNums,fp);
    }
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
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=1;i<=15;i++)
    {
        int c =palSpace * i;
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
    //RGB
    for(int i=0;i<colorNums;i++)
    {
        for(int j=0;j<colorNums;j++){
            for(int k=0;k<colorNums;k++){
                PalColorMat[3 * colorNums + i*colorNums*colorNums + j*colorNums +k][0] = PalColorMat[i][0];
                PalColorMat[3 * colorNums + i*colorNums*colorNums + j*colorNums +k][1] = PalColorMat[colorNums + j][0];
                PalColorMat[3 * colorNums + i*colorNums*colorNums + j*colorNums +k][2] = PalColorMat[colorNums*2 + k][0];
            }
        }
    }

}


int MainDisplay::paintPal(Palette pal,QPainter painter){
    painter.save();
    QPen  pen;
    pen.setColor(QColor(255,255,255));
    QBrush brush(QColor(pal.rgb_Red,pal.rgb_Green,pal.rgb_Blue));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(pal.xloc,pal.yloc,pal.width,pal.height);
    painter.restore();
    return 1;
}
int MainDisplay::paintSector(Sector sector,QPainter painter){
    painter.save();//save painter status
    QRectF pieRect(sector.xloc,sector.yloc,sector.width,sector.height);//rectangle of sector
    QPen pen;
    pen.setColor(Qt::white);//set color 、style of pen
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);//set pen to painter
    //draw pie
    painter.drawPie(pieRect,sector.startAngle,sector.spanAngle);
    //绘制扇形上的圆弧
    for(int i=1;i<sector.radCalNum;i++){
        int x,y,wInc,hInc,w,h;
        wInc = i * sector.width / sector.radCalNum;
        hInc = i * sector.height / sector.radCalNum;
        x = sector.xloc + wInc / 2;
        y = sector.yloc + hInc / 2;
        w = sector - wInc;
        h = sector-hInc;
        painter.drawArc(x,y,w,h,sector.startAngle,sector.spanAngle);
    }

    //painter.setRenderHint(QPainter::Antialiasing, true);//open Antialiasing
    //    进行坐标系变换 从扇形的坐标移动到扇形的中心点处
    painter.translate(sector.xloc+0.5*sector.width,sector.yloc + 0.5*sector.height);
    //旋转到起始角度
    int angle = 180-sector.endAngle;
    if(angle < 0){
        angle = 360-sector.endAngle;
    }
    painter.rotate(angle);
    for(int i=0;i<sector.arcCalNum;i++){
        painter.rotate(sector.rotateAngle);
        //从中心点移动到扇形左边
        if((i+1) % sector.numSystem == 0){//绘制大刻度线
            painter.drawLine(-0.5*sector.width,0,0,0);
        }
        //绘制一般的小刻度线
        painter.drawLine(-0.5*sector.width,0,-0.5*sector.width+sector.arcCalWidth,0);
    }
    painter.restore();
    return 1;
}
