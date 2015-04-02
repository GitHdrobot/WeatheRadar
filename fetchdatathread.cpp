#include "fetchdatathread.h"
#include "rvp900.h"
/*构造函数*/
FetchDataThread::FetchDataThread(QObject *parent) :
		QObject(parent) {
	flag = 0;

	threadFlag = false;
}

void FetchDataThread::run() {
	int i = 0;
    while (threadFlag) {
		if (int c = rvp9.PROC(outbuff) != RVP_NO_ERR) {
			return SOCKET_READ_ERR;
		}
    for(i=0;i<BINS_HEADER_LEN;i++) {
		TAGBuff[i] = outBuff[i];
	}
    for(;i<BINS_HEADER_LEN + BINS_NUM;i++){
		binsWBuff[i] = outBuff[i];
	}
    for(;i<BINS_HEADER_LEN + 2*BINS_NUM;i++){
			binsVBuff[i] = outBuff[i];
		}
    for(;i<BINS_HEADER_LEN + 3*BINS_NUM;i++){
			binsTBuff[i] = outBuff[i];
		}
    for(;i<BINS_HEADER_LEN + 4*BINS_NUM;i++){
			binsZBuff[i] = outBuff[i];
		}
}
}
