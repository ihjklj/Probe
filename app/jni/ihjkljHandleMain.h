
#ifndef __IHJKLJ_HANDLE_H__
#define __IHJKLJ_HANDLE_H__

#include "nativeUtil.h"
#include "ihjkljSocketClient.h"
#include "ihjkljSocketServer.h"

class CHandleMain {
public:
    CHandleMain(JavaVM *vm);
    ~CHandleMain();

    void init(JavaVM *vm);
    void start();
    void stop();
    void setQosInterval(int duration);
    void sendFrameToQos(const char *frameInfo);
    void setValue(const char *key, const char *value);
    CSocketServer& getServer() { return mServer; }
    CSocketClient& getClient() { return mClient; }

protected:
    int praseInfo(const char* szInf, char* spbuf[]);

public:
    static jclass       mJniClass;
    static jmethodID    mJniMethodId;

protected:
    CSocketServer      mServer;
    CSocketClient      mClient;
    CThread*            mHandleThread;
    JavaVM*             mJavavm;
};



#endif /* __IHJKLJ_HANDLE_H__ */

