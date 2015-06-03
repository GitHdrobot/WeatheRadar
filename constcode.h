/*
*显示界面上的一些常量设置
*/
#ifndef CONSTCODE_H
#define CONSTCODE_H

#define MODE1_4_PIC 1 //方式1 4图
#define MODE2_2_DBZT 2
#define MODE2_2_DBZV 3
#define MODE2_2_DBZW 4
#define MODE2_2_DBTV 5
#define MODE2_2_DBTW 6

#define MODE3_1_DBZ 6 //方式3一图DBZ
#define MODE3_1_DBT 7
#define MODE3_1_V 8
#define MODE3_1_W 9

#define MODE_1PIC 1   //一图
#define MODE_2PIC 2   //两图
#define MODE_4PIC 4   //四图

#define CONFIG_WIDTH 365  //右侧设置面板占据的宽度
#define TOP_BOTTOM_HEIGHT 7 //上下占据的高度
#define PI 3.1415926

/*颜色每隔16取1个*/
const int colorSpace = 8;
/*选择16种颜色进行配色*/
const int choosenColorNum = 16;
/*1K种颜色*/
const int palColorNum  = 300;
/*扇形起始角度*/
const int startAngle  = 30;
/*扇形跨度*/
const int spanAngle  = 120;
/*色标的个数*/
const int shadeGuadeNum = 15;
/*最小角度1°*/
const int minAngle = 1;
/*基础颜色个数*/
const int baseColorNum = 3;
/*调色板个数*/
const int palNum = 15;
/*Qt角度的度量用的是一度的十六分之一*/
const int angleFactor = 16;
//
const int palSectorXInter = 20;
const int palSectorYInter = 250;

#define TTY_DEV0 "/dev/ttyS0" //端口路径 如果是在电脑端选择ttyUSB,在mini2440端则选择ttySAC
#define TTY_DEV1 "/dev/ttyS1"
#define TTY_DEV2 "/dev/ttyS2"
#define TTY_DEV3 "/dev/ttyS3"
#define TTY_DEV4 "/dev/ttyUSB0"
#define TTY_DEV5 "/dev/ttyUSB1"


#endif // CONSTCODE_H
