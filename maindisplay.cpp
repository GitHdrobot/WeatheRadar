#include "maindisplay.h"

extern RVP900 rvp9;//rvp9控制对象
extern int colorTotal;
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
    //计算出每个色标代表的值
    short perdBZ = (dBZMax - dBZMin )/palNum;
    char formatter[10];
    //设置色标填充颜色,位置
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c = 16*  i;
        pal[i].setFillRed(PalColorMat[c][0]);
        pal[i].setFillGreen(PalColorMat[c][1]);
        pal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        pal[i].setXloc( 50 );
        pal[i].setYloc (350);
        pal[i].yloc -= i * pal[i].height;
        sprintf(formatter,"%d",dBZMin + i*perdBZ);
        pal[i].setComTxt(formatter);
        paintPal(pal[i]);
    }

}

void MainDisplay::paintDBTPal(Palette pal[],int palLenth){
    //计算出每个色标代表的值
    short perdBZ = (dBZMax - dBZMin )/palNum;
    char formatter[10];
    //设置色标填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].setFillRed(PalColorMat[c][0]);
        pal[i].setFillGreen(PalColorMat[c][1]);
        pal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        pal[i].setXloc(100);
        pal[i].setYloc(100);
        pal[i].yloc += i * pal[i].height;
        sprintf(formatter,"%d",perdBZ*i+dBZMin);
        pal[i].setComTxt(formatter);
        paintPal(pal[i]);
    }
}

void  MainDisplay::paintWPal(Palette pal[],int palLenth){
    float Vmax = rvp9.getVmax();
    //计算出每个色标表示多少
    float perVmax = Vmax / palNum;
    char formatter[10];
    //设置色标填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].setFillRed(PalColorMat[c][0]);
        pal[i].setFillGreen(PalColorMat[c][1]);
        pal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        pal[i].setXloc( 150);
        pal[i].setYloc(150);
        pal[i].yloc += i * pal[i].height;
        sprinf(formatter,"%.1f",perVmax*i);
        pal[i].setComTxt(formatter);
        paintPal(pal[i]);
    }
}

void  MainDisplay::paintVPal(Palette pal[],int palLenth){
    float Vmax = rvp9.getVmax();
    //计算出每个色标表示多少
    float perVmax = Vmax*2 / palNum;
    //计算出负的最大速度
    float Vmaxs =Vmax * -1;
    char formatter[10];
    //设置色标填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        pal[i].setFillRed(PalColorMat[c][0]);
        pal[i].setFillGreen(PalColorMat[c][1]);
        pal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        pal[i].setXloc(200);
        pal[i].setYloc(200);
        pal[i].yloc += i * pal[i].height;
        //从最大负数开始 每循环一次增加一个量度的速度
        sprintf(formatter,"%0.1f",Vmaxs + i*perVmax);
        pal[i].setComTxt(formatter);
        paintPal(pal[i]);
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
        hInc = i * sector.height / sector.radCalNum;
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
    //设置扇形的位置、大小
    sector.setXloc(100);
    sector.setYloc(100);
    sector.setWidth(500);
    sector.setHeight(500);
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
    //color B 单色
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
    colorTotal = cursor;
}

int MainDisplay::paintDBZ(){
    startPaint(rvp9.binsZBuff);
}

int MainDisplay::paintDBT(){
    startPaint(rvp9.binsTBuff);
}

int MainDisplay::paintV(){
    startPaint(rvp9.binsVBuff);
}

int MainDisplay::paintW(){
    startPaint(rvp9.binsWBuff);
}

int MainDisplay::startPaint(unsigned char buff){
    unsigned short azimuthus ;
    //dbz坐标位置的计算
    QPoint dbzPoint;
    //将角度转换为十进制数
    azimuthus=(((unsigned char)rvp9.binsTAGBuff[0]+(unsigned char)rvp9.binsTAGBuff[1]*256)>>4);
    //转换为角度
    float azimuthf=float(azimuthus)*360.0/4096.0+0.5;
    //计算出该角度在哪一个象限内 根据不同象限 计算出改点的坐标位置
    int quadrant  ;
    //扇形半径
    int radius = sector.getWidth()/2;
    float azimuthIncf;
    QPoint center = sector.calculateCenter();
    //dbz颜色均分
    QPen pen ;
    float colorPerDBZ = colorTotal / dBZMax;
    //<1 度范围内的绘制
    for(int j =0;j< 1 ;j+=0.2){
        azimuthIncf = azimuthf + i;
        quadrant = azimuthIncf / 90;
        for(int i=0;i<radius;i++){
            switch(quadrant){
            //第一象限
            case 0:
                dbzPoint.setX(center.x() + radius*sin(azimuthIncf*PI/180));
                dbzPoint.setY(center.y() - radius*cos(azimuthIncf*PI/180));
                break;
                //第二象限
            case 1:
                dbzPoint.setX(center.x() - radius*sin(azimuthIncf*PI/180));
                dbzPoint.setY(center.y() - radius*cos(azimuthIncf*PI/180));
                break;
                //第三象限
            case 2:
                dbzPoint.setX(center.x() - radius*sin(azimuthIncf*PI/180));
                dbzPoint.setY(center.y() + radius*cos(azimuthIncf*PI/180));
                break;
            case 3:
                //第四象限
                dbzPoint.setX(center.x() + radius*sin(azimuthIncf*PI/180));
                dbzPoint.setY(center.y() + radius*cos(azimuthIncf*PI/180));
                break;
            }

            //计算颜色
            int  colorIndex = buff[i] * colorPerDBZ;
            //设置画笔颜色
            pen.setColor(PalColorMat[colorIndex]);
            painter.drawPoint(dbzPoint);
        }
    }
}
