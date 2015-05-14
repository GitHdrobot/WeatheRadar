#include "maindisplay.h"


MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent)
{
    colorNums = 50;

    /*读取配置文件 文件打开成功 **/
    FILE *fp;
    if((fp=fopen("Palette.dat","rb")))
    {
        //printf("打开调色板成功\n");
        fread(PalColorMat,1,palColorNum*3,fp);
        fclose(fp);
    }else{
        if(fp=fopen("Palette.dat","wb")){
            colorBinFactory();
            fwrite(PalColorMat,1,palColorNum*3,fp);
            fclose(fp);
        }
    }

}

MainDisplay::~MainDisplay()
{
    delete []pal;
    delete &sector;
}

void MainDisplay::paintEvent(QPaintEvent *){
    painter.begin(this);
    setAutoFillBackground(true);
    paintShadeGuide();
    paintSectorManager();
}

void MainDisplay::paintShadeGuide() {
    int palLenth = 15;
    paintDBZPal(pal,palLenth);

}

void  MainDisplay::paintDBZPal(Palette pal[],int palLenth){
    //设置调色板填充颜色,位置
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c = 16*  i;
        pal[i].fillRed =PalColorMat[c][0];
        pal[i].fillGreen = PalColorMat[c][1];
        pal[i].fillBlue = PalColorMat[c][2] ;
        //调色板位置
        pal[i].xloc = 50;
        pal[i].yloc = 350;
        pal[i].yloc -= i * pal[i].height;
        paintPal(pal[i]);
    }

}

void MainDisplay::paintDBTPal(Palette pal[],int palLenth){
    //设置调色板填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].fillRed =PalColorMat[c][0];
        pal[i].fillGreen = PalColorMat[c][1];
        pal[i].fillBlue = PalColorMat[c][2] ;
        //调色板位置
        pal[i].xloc = 100;
        pal[i].yloc = 100;
        pal[i].yloc += i * pal[i].height;
        paintPal(pal[i]);
    }
}

void  MainDisplay::paintWPal(Palette pal[],int palLenth){
    //设置调色板填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].fillRed =PalColorMat[c][0];
        pal[i].fillGreen = PalColorMat[c][1];
        pal[i].fillBlue = PalColorMat[c][2] ;
        //调色板位置
        pal[i].xloc = 150;
        pal[i].yloc = 150;
        pal[i].yloc += i * pal[i].height;
        paintPal(pal[i]);
    }
}

void  MainDisplay::paintVPal(Palette pal[],int palLenth){
    //设置调色板填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].fillRed =PalColorMat[c][0];
        pal[i].fillGreen = PalColorMat[c][1];
        pal[i].fillBlue = PalColorMat[c][2] ;
        //调色板位置
        pal[i].xloc = 200;
        pal[i].yloc = 200;
        pal[i].yloc += i * pal[i].height;
        paintPal(pal[i]);
    }
}

void MainDisplay::colorPalFactory(){
    int space = 256 / colorNums;
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
                PalColorMat[3 * colorNums + i*colorNums*colorNums + j*colorNums +k][1] = PalColorMat[colorNums + j][1];
                PalColorMat[3 * colorNums + i*colorNums*colorNums + j*colorNums +k][2] = PalColorMat[colorNums*2 + k][2];
            }
        }
    }

}


int MainDisplay::paintPal(Palette pal){
    painter.save();
    QRectF palRect(pal.xloc,pal.yloc,pal.width,pal.height);
    QPen  pen;
    pen.setWidth(pal.frameWidth);
    pen.setColor(QColor(255,255,255));
    QBrush brush(QColor(pal.fillRed,pal.fillGreen,pal.fillBlue));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(palRect);
    QRectF txtRect(palRect);
    txtRect.setX(txtRect.x() + txtRect.width() + 3);
    txtRect.setWidth(txtRect.width()/2);
    painter.drawText(txtRect,pal.comTxt);
    painter.restore();
    return 1;
}

int MainDisplay::paintSector(){
    painter.save();//save painter status
    QRectF pieRect(sector.xloc,sector.yloc,sector.width,sector.height);//rectangle of sector
    QPen pen;
    pen.setColor(Qt::white);//set color 、style of pen
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);//set pen to painter
    //draw pie
    painter.drawPie(pieRect,sector.startAngle*angleFactor,sector.spanAngle*angleFactor);
    //绘制扇形上的圆弧
    for(int i=1;i<sector.radCalNum;i++){
        int x,y,wInc,hInc,w,h;
        wInc = i * sector.width / sector.radCalNum;
        hInc = i * sector.height / sector.radCalNum;-
        x = sector.xloc + wInc / 2;
        y = sector.yloc + hInc / 2;
        w = sector.width - wInc;
        h = sector.height-hInc;
        painter.drawArc(x,y,w,h,sector.startAngle*angleFactor,sector.spanAngle*angleFactor);
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
int MainDisplay:: paintSectorManager(){
    sector.xloc = 100;
    sector.yloc = 100;
    sector.width = 500;
    sector.height = 500;
    paintSector();
}
int MainDisplay:: colorBinFactory(){
    int cursor = 0;
    //color G单色
    for(int i=0;i<colorNums;i++){
        PalColorMat[ i][0] = 0;
        PalColorMat[ i][1] = 50+4*i;
        PalColorMat[ i][2] = 0 ;
    }
    cursor+=colorNums;
    //color BG 混色
    for(int i=0;i<colorNums;i++){
        PalColorMat[cursor + i][0] = 0;
        PalColorMat[cursor + i][1] =PalColorMat[colorNums - 1-i][1];
        PalColorMat[cursor + i][2] = 50+4*i;
    }
    cursor+=colorNums;
    //color B 单色32种
    for(int i=0;i<colorNums;i++){
        PalColorMat[cursor + i][0] = 0;
        PalColorMat[cursor + i][1] = 0;
        PalColorMat[cursor + i][2] = 50+4*i;
    }
    cursor+=colorNums;
    //color BR 混色
    for(int i=0;i<colorNums;i++){
        PalColorMat[cursor+i][0] = 15+4*i;
        PalColorMat[cursor+i][1] = 0;
        PalColorMat[cursor+i][2] =  PalColorMat[3*colorNums-1-i][2];
    }
    cursor+=colorNums;
    //color R 单色
    for(int i=0;i<colorNums;i++){
        PalColorMat[cursor + i][0] =15+4*i;
        PalColorMat[cursor + i][1] = 0;
        PalColorMat[cursor + i][2] = 0;
    }
    cursor+=colorNums;
    //color GR 混色
    for(int i=0;i<colorNums;i++){
        PalColorMat[cursor+i][0] = PalColorMat[3*colorNums+i][0];
        PalColorMat[cursor+i][1] = PalColorMat[i][1];
        PalColorMat[cursor+i][2] = 0;
    }
    cursor+=colorNums;
}
