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
    delete []dBZPal;
    delete []dBTPal;
    delete []vPal;
    delete []wPal;

    delete &dBZSector;
    delete &dBTSector;
    delete &vSector;
    delete &wSector;
}

void MainDisplay::paintEvent(QPaintEvent *){
    painter.begin(this);
    setAutoFillBackground(true);
    paintManager();
}


void  MainDisplay::paintDBZPal(Palette dbzPal[],int palLenth,QPoint slt){
    //计算出每个色标代表的值
    short perdBZ = (dBZMax - dBZMin )/palNum;
    char formatter[10];
    //设置色标填充颜色,位置
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c = 16*  i;
        dbzPal[i].setFillRed(PalColorMat[c][0]);
        dbzPal[i].setFillGreen(PalColorMat[c][1]);
        dbzPal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        dbzPal[i].setXloc( slt.x()-10 );
        dbzPal[i].setYloc (slt.y());
        dbzPal[i].yloc -= i * dbzPal[i].height;
        sprintf(formatter,"%d",dBZMin + i*perdBZ);
        dbzPal[i].setComTxt(formatter);
        paintPal(dbzPal[i]);
    }

}

void MainDisplay::paintDBTPal(Palette dbtPal[],int palLenth,QPoint slt){
    //计算出每个色标代表的值
    short perdBZ = (dBZMax - dBZMin )/palNum;
    char formatter[10];
    //设置色标填充颜色,位置
    int palSpace = colorNums * colorNums * colorNums /15;
    for(int i=0;i<palLenth;i++)
    {
        //颜色
        int c =palSpace * i;
        dbtPal[i].setFillRed(PalColorMat[c][0]);
        dbtPal[i].setFillGreen(PalColorMat[c][1]);
        dbtPal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        dbtPal[i].setXloc(slt.x()-10);
        dbtPal[i].setYloc(slt.y());
        dbtPal[i].yloc += i * dbtPal[i].height;
        sprintf(formatter,"%d",perdBZ*i+dBZMin);
        dbtPal[i].setComTxt(formatter);
        paintPal(dbtPal[i]);
    }
}

void  MainDisplay::paintWPal(Palette wPal[],int palLenth,QPoint slt){
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
        wPal[i].setFillRed(PalColorMat[c][0]);
        wPal[i].setFillGreen(PalColorMat[c][1]);
        wPal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        wPal[i].setXloc(slt.x()-10);
        wPal[i].setYloc(slt.y());
        wPal[i].yloc += i * wPal[i].height;
        sprintf(formatter,"%.1f",perVmax*i);
        wPal[i].setComTxt(formatter);
        paintPal(wPal[i]);
    }
}

void  MainDisplay::paintVPal(Palette vPal[],int palLenth,QPoint slt){
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
        vPal[i].setFillRed(PalColorMat[c][0]);
        vPal[i].setFillGreen(PalColorMat[c][1]);
        vPal[i].setFillBlue(PalColorMat[c][2]) ;
        //色标位置
        vPal[i].setXloc(slt.x()-10);
        vPal[i].setYloc(slt.y());
        vPal[i].yloc += i * vPal[i].height;
        //从最大负数开始 每循环一次增加一个量度的速度
        sprintf(formatter,"%0.1f",Vmaxs + i*perVmax);
        vPal[i].setComTxt(formatter);
        paintPal(vPal[i]);
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

int MainDisplay::paintSector(Sector *pSector){
    painter.save();//save painter status
    QRectF pieRect(pSector->xloc,pSector->yloc,pSector->width,pSector->height);//rectangle of sector
    QPen pen;
    pen.setColor(Qt::white);//set color 、style of pen
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);//set pen to painter
    //draw pie
    painter.drawPie(pieRect,pSector->startAngle*angleFactor,pSector->spanAngle*angleFactor);
    //绘制扇形上的圆弧
    for(int i=1;i<pSector->radCalNum;i++){
        int x,y,wInc,hInc,w,h;
        wInc = i * pSector->width / pSector->radCalNum;
        hInc = i * pSector->height / pSector->radCalNum;
        x = pSector->xloc + wInc / 2;
        y = pSector->yloc + hInc / 2;
        w = pSector->width - wInc;
        h = pSector->height-hInc;
        painter.drawArc(x,y,w,h,pSector->startAngle*angleFactor,pSector->spanAngle*angleFactor);
    }

    //painter.setRenderHint(QPainter::Antialiasing, true);//open Antialiasing
    //    进行坐标系变换 从扇形的坐标移动到扇形的中心点处
    painter.translate(pSector->xloc+0.5*pSector->width,pSector->yloc + 0.5*pSector->height);
    //旋转到起始角度
    int angle = 180-pSector->endAngle;
    if(angle < 0){
        angle = 360-pSector->endAngle;
    }
    painter.rotate(angle);
    for(int i=0;i<pSector->arcCalNum;i++){
        painter.rotate(pSector->rotateAngle);
        //从中心点移动到扇形左边
        if((i+1) % pSector->numSystem == 0){//绘制大刻度线
            painter.drawLine(-0.5*pSector->width,0,0,0);
        }
        //绘制一般的小刻度线
        painter.drawLine(-0.5*pSector->width,0,-0.5*pSector->width+pSector->arcCalWidth,0);
    }
    painter.restore();
    return 1;
}
int MainDisplay:: paintManager(){
    int palLenth = 15;
    QPoint  SLT;// sector left top
    //设置dBZ的位置、大小
    dBZSector.setXloc(100);
    dBZSector.setYloc(100);
    dBZSector.setWidth(400);
    dBZSector.setHeight(400);
    paintSector(&dBZSector);
    SLT.setX(100);
    SLT.setY(100);
    paintDBZPal(dBZPal,palLenth,SLT);//绘制dbz色标卡
    //设置dBT的位置、大小
    dBTSector.setXloc(550);
    dBTSector.setYloc(100);
    dBTSector.setWidth(400);
    dBTSector.setHeight(400);
    paintSector(&dBTSector);
    SLT.setX(550);
    SLT.setY(100);
    paintDBTPal(dBTPal,palLenth,SLT);//绘制dbt色标卡
    //设置V位置、大小
    vSector.setXloc(100);
    vSector.setYloc(200);
    vSector.setWidth(400);
    vSector.setHeight(400);
    paintSector(&vSector);
    SLT.setX(100);
    SLT.setY(200);
    paintVPal(dBTPal,palLenth,SLT);//绘制v色标卡
    //设置W位置、大小
    wSector.setXloc(550);
    wSector.setYloc(200);
    wSector.setWidth(400);
    wSector.setHeight(400);
    paintSector(&wSector);
    SLT.setX(550);
    SLT.setY(200);
    paintWPal(dBTPal,palLenth,SLT);//绘制w色标卡



    paintDBTPal(dBTPal,palLenth);
    paintVPal(vPal,palLenth);
    paintWPal(wPal,palLenth);

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
    startPaint(rvp9.binsZBuff,&dBZSector);
}

int MainDisplay::paintDBT(){
    startPaint(rvp9.binsTBuff,&dBTSector);
}

int MainDisplay::paintV(){
    startPaint(rvp9.binsVBuff,&vSector);
}

int MainDisplay::paintW(){
    startPaint(rvp9.binsWBuff,&wSector);
}

int MainDisplay::startPaint(unsigned char *pbuff,Sector *pSector){
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
    int radius = pSector->getWidth()/2;
    float azimuthIncf;
    QPoint center = pSector->calculateCenter();
    //dbz颜色均分
    QPen pen ;
    float colorPerDBZ = colorTotal / dBZMax;
    //<1 度范围内的绘制
    for(int j =0;j< 1 ;j+=0.2){
        azimuthIncf = azimuthf + j;
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
            int  colorIndex = pbuff[i] * colorPerDBZ;
            //设置画笔颜色
            QColor qcolor(PalColorMat[colorIndex][0],PalColorMat[colorIndex][1],PalColorMat[colorIndex][2]);
            pen.setColor(qcolor);
            painter.drawPoint(dbzPoint);
        }
    }
}
