
#include "ihjkljHandleMain.h"

CHandleMain::CHandleMain(JavaVM *vm) {
    mJavavm = vm;
    mHandleThread = NULL;
    mServer.init(mv, "127.0.0.1", 13980);
    mClient.init("127.0.0.1", 13978);
}

CHandleMain::~CHandleMain() {
    //
}

void CHandleMain::start() {
    mServer.start();
}

void CHandleMain::stop() {
    mServer.stop();
    mClient.closeTo();
}

int CHandleMain::praseInfo(const char* szInf, char* spbuf[]) {

    int i = 0;
    int num = 0;
    char tmpBuf[1024] = {0};
    char storn[2408] = {0};
    char* tmp = NULL;
    char* head = NULL;
    char* sptmp[64];

    head = storn;
    strcpy(storn, szInf);
    while ((sptmp[i] = strstr(head, ")"))) {
        memset(tmpBuf, 0x00, sizeof(tmpBuf));
        memcpy(tmpBuf, head, sptmp[i] - head + 1);
        if (tmpBuf[0] == 'I') {
            tmpBuf[0] = '1';
        } else if (tmpBuf[0] == 'P') {
            tmpBuf[0] = '2';
        } else if (tmpBuf[0] == 'B') {
            tmpBuf[0] = '3';
        }  else {
            tmpBuf[0] = '0';
        }
        head = sptmp[i] + 2;
        sptmp[i] = strdup((const char*)tmpBuf);
        i++;
        num++;
    }

    if (num > 0){
        memcpy((void *)spbuf, (void *)sptmp, num * sizeof(char *));
    }

    return num;
}

void CHandleMain::sendFrameToQos(const char *frameInfo) {
    int num = -1, i, seat, nouse;
    char* strinf[64] = {0};
    char* tmp = NULL;

    tmp = strstr(szInf, "frame_info:") + strlen("frame_info:");
    num = praseInfo(tmp, strinf);

    VIDEO_FRAME_INFO frameInfo;
    memset(&frameInfo, 0, sizeof(VIDEO_FRAME_INFO));

    if (num <= 0)
        return;

	QOSCMD cmd;
	cmd.cmd = FrameInfo;
	int enum_t = -1;
	for (i = 0, seat = 0; i < num; i++, seat++) {
		sscanf(strinf[i], "%d(%d,%d,%d,%d,%d,%d,%d,%d,%d)", &enum_t, &(frameInfo.nFrmSize), &(frameInfo.nMinQP), &(frameInfo.nMaxQP), &(frameInfo.nAvgQP),
			   &(frameInfo.nMinMV), &(frameInfo.nMaxMV), &(frameInfo.nAvgMV), &(frameInfo.SkipRatio), &frameInfo.decoderbuffer);
		frameInfo.enVidFrmType = enum_t;
		memcpy(cmd.v.szValue + seat * sizeof(VIDEO_FRAME_INFO), &frameInfo, sizeof(VIDEO_FRAME_INFO));
		if (seat == 20) {
			cmd.len = seat * sizeof(VIDEO_FRAME_INFO);
			mClient.sendToServer(&cmd);
			memset(cmd.v.szValue, 0, strlen(cmd.v.szValue));
			seat = -1;
		}
		free(strinf[i]);
		memset(&frameInfo, 0, sizeof(VIDEO_FRAME_INFO));
	}
	if (seat > 0) {
		cmd.len = seat * sizeof(VIDEO_FRAME_INFO);
		mClient.sendToServer(&cmd);
	}
}

void CHandleMain::setQosInterval(int duration) {
    QOSCMD cmd;
    cmd.cmd = SetQOSInterval;
    cmd.v.nValue = duration;
    mClient.sendToServer(&cmd);
}

void CHandleMain::setValue(const char *key, const char *value) {
    QOSCMD cmd;
    cmd.cmd = SetMsgToQos;
    snprintf(cmd.v.szValue, SZ_VALUE_LEN, "key:%s,value:%s", key, value);

    mClient.sendToServer(&cmd);
}

