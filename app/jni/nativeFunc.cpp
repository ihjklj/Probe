
#include "nativeFunc.h"

JavaVM *gJvm = NULL;

JNIEXPORT void JNICALL NAME(start)(JNIEnv *env, jobject object){
    LOGD("---->");
    return ;
}

JNIEXPORT void JNICALL NAME(stop)(JNIEnv *env, jobject thiz){
    LOGD("---->");
}

JNIEXPORT void JNICALL NAME(setQosInterval)(JNIEnv *env, jobject thiz, jint nDura){
    LOGD("---->");
}

JNIEXPORT void JNICALL NAME(setValue)(JNIEnv *env, jobject thiz, jstring jstrKey, jstring jstrValue){
    LOGD("---->");
}

JNIEXPORT void JNICALL NAME(sendFrameInfo)(JNIEnv *env, jobject thiz, jstring jstrInf){
    LOGD("---->");
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    gJvm = vm;
    LOGD("enter, ver:%s\n", VERTIME);
    return JNI_VERSION_1_4;
}