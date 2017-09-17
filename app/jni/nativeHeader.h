
#ifndef __NATIVE_HEADER_H__
#define __NATIVE_HEADER_H__

#include <jni.h>

#define CLASS Java_com_ihjklj_probe_androidnative_NativeMethod_

#define NAME2(CLS, FUN) CLS##FUN
#define NAME1(CLS, FUN) NAME2(CLS, FUN)
#define NAME(FUN) NAME1(CLASS, FUN)

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL NAME(start)(JNIEnv *env, jobject object);

#ifdef __cplusplus
}
#endif

#endif /* __NATIVE_HEADER_H__ */