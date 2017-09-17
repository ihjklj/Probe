
#ifndef __C_THREAD_H__
#define __C_THREAD_H__

#include <jni.h>
#include "nativeUtil.h"

typedef  int (*PTHREAD_ROUTINE)(void* lParam);

class CThread {
public:
    CThread(JavaVM *vm, PTHREAD_ROUTINE func, void *lParm);
    virtual ~CThread();

    static void* runThreadFunc(void *data);
    pthread_t getThreadId() { return mThreadId; }

protected:
    JavaVM*             mJavaVm;
    pthread_t           mThreadId;
    void*               mParm;
    PTHREAD_ROUTINE     mThreadFunc;
    bool                mExit;
};








#endif /* __C_THREAD_H__ */
