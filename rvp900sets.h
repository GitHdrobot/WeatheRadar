#ifndef RVP900SETS_H
#define RVP900SETS_H


class RVP900Sets
{
public:
    RVP900Sets();
    ~RVP900Sets();
public:
    //距离库个数 与距离掩码设置位个数相同
   int binsNum;
   //采集数据种类 dBz,dBt,dBw,v，默认为ALL
   enum dataType {Z_BIT,T_BIT,V_BIT,W_BIT,ALL};
   //采集的数据是否包含 头部TAG，默认为true
   bool dataHeader;
    //距离量程 distance range,目前仅设置六个距离范围
   enum disRange {RANGE_FIRST,RANGE_SECOND,RANGE_THIRD,RANGE_FOURTH,RANGE_FIFTH,RANGE_SIXTH};
   //脉冲重复频率
   enum PRF {PRF_FIRST,PRF_SECOND,PRF_THIRD,PRF_FOURTH,PRF_FIFTH,PRF_SIXTH};
   /*数据采集方式 collect mode,有三种Synchronous，
    *free running，time series，默认是time series
    */
    enum colMode {SYNCHRONOUS,FREE_RUNNING,TIME_SERIES};
    //脉冲宽度
    int pulseWidth;
    //双PRF，脉冲重复比,此处不是真实比率
    enum PRF_Ratio{NONE,THREE_TO_TWO,FOUR_TO_THREE,FIVE_TO_FOUR};
    //多普勒滤波器 doppler filter
    enum dopFilter {NONE,ONE,TWO,THREE,FOUTH,FIVE,SIX,SEVEN};
    //处理模式 processing mode
    enum proMode {PPP,FFT,RPP,DPRT_1,DPRT_2};
    //脉冲累积数
    enum pulAccumulate {};
    //Threshold of LOG、SIG、CCOR、SQI,门限值
    float LOG_Threshold,SIG_Threshold,CCOR_Threshold,SQI_Threshold;
    //R2使能
    bool RTwoEnable;
    //距离平均
    int avgDistance;
};

#endif // RVP900SETS_H
