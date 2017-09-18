
#ifndef __IHJKLJ_HANDLE_H__
#define __IHJKLJ_HANDLE_H__

#include "nativeUtil.h"
#include "ihjkljSocketClient.h"
#include "ihjkljSocketServer.h"

class CHandleMain {
public:
    CHandleMain(JavaVM *vm);
    ~CHandleMain();

    void start();
    void stop();
    void setQosInterval(int duration);
    void sendFrameToQos(const char *frameInfo);
    void setValue(const char *key, const char *value);

protected:
    int praseInfo(const char* szInf, char* spbuf[]);

protected:
    CSoceketServer      mServer;
    CSoceketClient      mClient;
    CThread*            mHandleThread;
    JavaVM*             mJavavm;
};



#endif /* __IHJKLJ_HANDLE_H__ */

