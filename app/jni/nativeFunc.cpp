
#include "nativeFunc.h"

JavaVM *gJvm = NULL;
CHandleMain gHandle;

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
}

JNIEXPORT void JNICALL NAME(setValue)(JNIEnv *env, jobject thiz, jstring jstrKey, jstring jstrValue){
    LOGD("---->");

    if (jstrKey == NULL || jstrValue == NULL){
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
    LOGD("---->");
    if (jstrInf == NULL){
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
    jvm->GetEnv((void **)&env, JNI_VERSION_1_4);
    if (env == NULL){
        jvm->AttachCurrentThread(&env, NULL);
    }
    return env;
}

void uploadData(const char* dType, const char* aType, const char* data) {
    if (dType == NULL || aType == NULL || data == NULL)
        return;
    if (clsQosService == NULL || midOnDataUpload == NULL){
        return;
    }
    JNIEnv* env = GetJNIEnv();
    if (env == NULL){
        return;
    }
    jstring strDType = env->NewStringUTF(dType);
    jstring strAType = env->NewStringUTF(aType);
    jstring strData = env->NewStringUTF(data);
    env->CallStaticVoidMethod(clsQosService, midOnDataUpload, strDType, strAType, strData);
    CHECKERR(env);
    env->DeleteLocalRef(strDType);
    env->DeleteLocalRef(strAType);
    env->DeleteLocalRef(strData);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    gJvm = vm;

    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!\n");
        return -1;
    }
    jclass cls = env->FindClass("com/ihjklj/probe/androidnative/NativeMethod");
    CHECKERR(env);
    if (cls != NULL){
        midOnDataUpload = env->GetStaticMethodID(cls, "onDataUpload", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        CHECKERR(env);
        clsQosService = (jclass)env->NewGlobalRef(cls);
    }

    gHandle.init(vm);
    gHandle.getServer().setListener(uploadData);
    LOGD("enter, ver:%s\n", VERTIME);
    return JNI_VERSION_1_4;
}