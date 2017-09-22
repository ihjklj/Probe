
#include "ikNativeFunc.h"
#include "ikHandleMain.h"

JavaVM *gJvm = NULL;
CHandleMain gHandle;
jmethodID gOnDataUpload = NULL;
jclass gQosService = NULL;

JNIEXPORT void JNICALL NAME(start)(JNIEnv *env, jobject object){
    LOGD("---->");
    gHandle.start();
    return ;
}

JNIEXPORT void JNICALL NAME(stop)(JNIEnv *env, jobject thiz){
    LOGD("---->");
    gHandle.stop();
}

JNIEXPORT void JNICALL NAME(setQosInterval)(JNIEnv *env, jobject thiz, jint nDura){
    LOGD("---->");
    gHandle.setQosInterval(nDura);
}

JNIEXPORT void JNICALL NAME(setValue)(JNIEnv *env, jobject thiz, jstring jstrKey, jstring jstrValue){
    if (jstrKey == NULL || jstrValue == NULL){
        LOGE("jstrKey or jstrValue is NULL!");
        return ;
    }

    const char *key = env->GetStringUTFChars(jstrKey, NULL);
    const char *value = env->GetStringUTFChars(jstrValue, NULL);
    if (key != NULL && value != NULL){
        gHandle.setValue(key, value);
    }

    if (key != NULL){
        env->ReleaseStringUTFChars(jstrKey, key);
    }
    if (value != NULL){
        env->ReleaseStringUTFChars(jstrValue, value);
    }
}

JNIEXPORT void JNICALL NAME(sendFrameInfo)(JNIEnv *env, jobject thiz, jstring jstrInf){
    if (jstrInf == NULL){
        LOGE("jstrInf is NULL!");
        return ;
    }

    const char *frame = env->GetStringUTFChars(jstrInf, NULL);
    if (frame != NULL){
        gHandle.sendFrameToQos(frame);
        env->ReleaseStringUTFChars(jstrInf, frame);
    }
}

JNIEnv* GetJNIEnv() {
    JNIEnv* env = NULL;
    gJvm->GetEnv((void **)&env, JNI_VERSION_1_4);
    if (env == NULL){
        gJvm->AttachCurrentThread(&env, NULL);
    }
    return env;
}

void uploadData(const char* dType, const char* aType, const char* data) {
    LOGD("dType:%s, aType:%s, data:%s.", aType, aType, data);
    if (dType == NULL || aType == NULL || data == NULL)
        return;
    if (gQosService == NULL || gOnDataUpload == NULL){
        return;
    }
    JNIEnv* env = GetJNIEnv();
    if (env == NULL){
        return;
    }
    jstring strDType = env->NewStringUTF(dType);
    jstring strAType = env->NewStringUTF(aType);
    jstring strData = env->NewStringUTF(data);
    env->CallStaticVoidMethod(gQosService, gOnDataUpload, strDType, strAType, strData);
    CHECKERR(env);
    env->DeleteLocalRef(strDType);
    env->DeleteLocalRef(strAType);
    env->DeleteLocalRef(strData);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("enter, ver:%s", VERTIME);
    gJvm = vm;
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!");
        return -1;
    }
    jclass cls = env->FindClass("com/ihjklj/probe/androidnative/NativeMethod");
    CHECKERR(env);
    if (cls != NULL){
        gOnDataUpload = env->GetStaticMethodID(cls, "onDataUpload", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        CHECKERR(env);
        gQosService = (jclass)env->NewGlobalRef(cls);
    }

    char serverHost[128] = {"127.0.0.1"};
    char clientHost[128] = {"127.0.0.1"};
    gHandle.init(vm, serverHost, clientHost, 13980, 13978);
    gHandle.getServer().setListener(uploadData);

    return JNI_VERSION_1_4;
}