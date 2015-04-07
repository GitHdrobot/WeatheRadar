/*
*显示界面上的一些常量设置
*/

#ifndef CONSTCODE_H
#define CONSTCODE_H

#define PI 3.1415926

#define MODE1_ARC_X 100.0
#define MODE1_ARC_Y 100.0
#define MODE1_ARC_W 500.0
#define MODE1_ARC_H 500.0

#define SPAN_ANGLE 120 //扇形跨度
#define START_ANGLE 30 //扇形起始角度
#define MODE1_ARC_ST_ANGLE START_ANGLE*16
#define MODE1_ARC_SP_ANGLE SPAN_ANGLE*16

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


#define ROTATE_ANGLE 30   // 旋转角度
#define ARC_NUM 5 //绘制的圆弧个数
#define MIN_GRADUATION 1  //最小刻度 1度
#define GRADUATION_LEN 3 //绘制刻度线的长度
#define GRADUATION_NUM SPAN_ANGLE / MIN_GRADUATION //绘制的刻度个数


#define MAX_VALUE 30 //上限值
#define COLOR_INTERVAL 10 //颜色间隔
#define VALUE_INTERVAL //间隔

#define DBZ_PAL_X 50  //DBZ 调色板大小、位置
#define DBZ_PAL_Y 50
#define DBZ_PAL_W 50
#define DBZ_PAL_H 20

#define DBT_PAL_X 150  //DBT 调色板大小、位置
#define DBT_PAL_Y 50
#define DBT_PAL_W 50
#define DBT_PAL_H 20

#define V_PAL_X 250  //速度普宽 调色板大小、位置
#define V_PAL_Y 50
#define V_PAL_W 50
#define V_PAL_H 20

#define W_PAL_X 350  //W 调色板大小、位置
#define W_PAL_Y 50
#define W_PAL_W 50
#define W_PAL_H 20

#define SHADE_GUADE_NUM 15 //调色板个数

#define PAL_COLOR_NUM 256 //256种颜色
#define BASE_COLOR_NUM 3    //基本原色个数

#define CONFIG_WIDTH 365  //右侧设置面板占据的宽度
#define TOP_BOTTOM_HEIGHT 7 //上下占据的高度



#endif // CONSTCODE_H
