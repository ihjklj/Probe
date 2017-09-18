
#ifndef __NATIVE_HEADER_H__
#define __NATIVE_HEADER_H__

#include "nativeUtil.h"

#define CLASS Java_com_ihjklj_probe_androidnative_NativeMethod_

#define NAME2(CLS, FUN) CLS##FUN
#define NAME1(CLS, FUN) NAME2(CLS, FUN)
#define NAME(FUN) NAME1(CLASS, FUN)

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL NAME(start)(JNIEnv *env, jobject object);
JNIEXPORT void JNICALL NAME(stop)(JNIEnv *env, jobject thiz);
JNIEXPORT void JNICALL NAME(setQosInterval)(JNIEnv *env, jobject thiz, jint nDura);
JNIEXPORT void JNICALL NAME(setValue)(JNIEnv *env, jobject thiz, jstring jstrKey, jstring jstrValue);
JNIEXPORT void JNICALL NAME(sendFrameInfo)(JNIEnv *env, jobject thiz, jstring jstrInf);

#ifdef __cplusplus
}
#endif

JNIEnv* GetJNIEnv();
void uploadData(const char* dType, const char* aType, const char* data);

#endif /* __NATIVE_HEADER_H__ */