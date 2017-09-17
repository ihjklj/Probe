
#include "CThread.h"

CThread::CThread(JavaVM *vm, PTHREAD_ROUTINE func, void *lParm) {
    mJavaVm = vm;
    mThreadFunc = func;
    mParm = lParm;
    mExit = false;
    if (pthread_create(&mThreadId, NULL, runThreadFunc, this) > 0){
        pthread_detach(mThreadId);
    }
}

CThread::~CThread() {
    //
}

void* CThread::runThreadFunc(void *data) {
    CThread *threadThis = (CThread *)data;

    JNIEnv* env = NULL;
    if (threadThis->mJavaVm != NULL)
        threadThis->mJavaVm->AttachCurrentThread(&env, NULL);
    threadThis->mThreadFunc(threadThis->mParm);
    threadThis->mExit = true;

    if (env == NULL)
        threadThis->mJavaVm->AttachCurrentThread(&env, NULL);
    if (env != NULL)
        threadThis->mJavaVm->DetachCurrentThread();
    pthread_exit(0);
    return NULL;
}