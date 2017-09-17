
#include <stdio.h>
#include "nativeHeader.h"
#include "nativeUtil.h"

JavaVM *gJvm = NULL;

JNIEXPORT void JNICALL NAME(start)(JNIEnv *env, jobject object){
    LOGD("---->");
    return ;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    gJvm = vm;
    LOGD("enter, ver:%s\n", VERTIME);
    return JNI_VERSION_1_4;
}