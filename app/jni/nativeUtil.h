
#ifndef __NATIVE_UTIL_H__
#define __NATIVE_UTIL_H__

#include <android/log.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define VER "333"
#define VERTIME __DATE__"@"__TIME__

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








#endif /* __NATIVE_UTIL_H__ */