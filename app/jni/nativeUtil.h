
#ifndef __NATIVE_UTIL_H__
#define __NATIVE_UTIL_H__

#include <stdio.h>
#include <android/log.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <errno.h>
#include <jni.h>

#define VER "333"
#define VERTIME __DATE__"@"__TIME__

#define closesocket(x) { shutdown(x, 2); close(x); (x) = -1; }
#define Sleep(x) usleep((x) * 1000);
#define CHECKERR(env) {if (env->ExceptionCheck()) {env->ExceptionDescribe();env->ExceptionClear();}}

typedef void (*UPLOAD_FUNC)(const char* , const char* , const char* );


#define LOGD(format, ...) 										\
		do { 													\
			__android_log_print(ANDROID_LOG_DEBUG, "QosSo", 	\
					"%s|%5d|%s| "format, 						\
					VER, 										\
					gettid(), 									\
					__FUNCTION__, 								\
					##__VA_ARGS__); 							\
		} while(0)

#define LOGV(format, ...) 										\
		do { 													\
			__android_log_print(ANDROID_LOG_VERBOSE, "QosSo", 	\
					"%s|%5d|%s| "format, 						\
					VER, 										\
					gettid(), 									\
					__FUNCTION__, 								\
					##__VA_ARGS__); 							\
		} while(0)

#define LOGE(format, ...) 									\
		do { 												\
			__android_log_print(ANDROID_LOG_ERROR, "Qos", 	\
					"%s|%5d|%s| "format, 					\
					VER, 									\
					gettid(), 								\
					__FUNCTION__, 							\
					##__VA_ARGS__); 						\
		} while(0)

#define LOGW(format, ...) 									\
		do { 												\
			__android_log_print(ANDROID_LOG_WARN, "QosSo", 	\
					"%s|%5d|%s| "format, 					\
					VER, 									\
					gettid(), 								\
					__FUNCTION__, 							\
					##__VA_ARGS__); 						\
		} while(0)

enum QosCmd {
	//FEC恢复组播包，传恢复的组播包数(nValue)
	Fec = 0,

	//播放过程中出现错误，传错误的信息(szValue)
	PlayErr,

	//缓冲区被取空（缓存下溢），传次数，如果每发生１次都传，则nValue为１
	Abend,

	//缓冲区上溢，传次数，如果每发生１次都传，则nValue为１
	UpAbend,

	//丢帧，传丢失的帧数（nValue)
	FrameLost,

	//缓冲开始时nValue为１，结束时nValue为０（注：是在播放过程中，而不是起播的时候，但是在起播时也缓冲几秒的数据时也需要调用)
	Buffering,

	//卡顿
	MultiZapping,

	//设置统计周期
	SetQOSInterval = 13,

	//设置值到Qos模块
	SetMsgToQos = 101,

	//播放信息
	PlayerStatus,

	//帧信息
	FrameInfo
};

#define ARR_VALUE_LEN	5
#define SZ_VALUE_LEN	1024

typedef struct {
	enum QosCmd cmd;	//命令值
	size_t len;			//msg长度
	union {
		int nValue;
		int arrValue[ARR_VALUE_LEN];
		char szValue[SZ_VALUE_LEN];
	}v;
} QOSCMD;






#endif /* __NATIVE_UTIL_H__ */