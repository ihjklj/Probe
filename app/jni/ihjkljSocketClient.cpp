
#include "ihjkljSocketClient.h"

CSocketClient::CSocketClient() {
    mSocketFd = -1;
    mPort = 0;
    mIsConnected = false;
    mHost = NULL;
}

CSocketClient::CSocketClient(const char *host, int port) {
    mSocketFd = -1;
    mPort = port;
    mIsConnected = false;
    mHost = host;
}

int CSocketClient::init(const char *host, int port) {
    mHost = host;
    mPort = port;
}

bool CSocketClient::connectTo() {
    int socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if (socketFd == -1){
        LOGE("socket failed!\n");
        return false;
    }

    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(host);
    clientAddr.sin_port = htons(mPort);

    struct timeval tv = {3, 0};

    /* 设置发送超时 */
    setsockopt(socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));

    /* 设置接收超时,因为加了线程锁所以这里设置接收超时就很有必要了 */
    setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));

    int nRet = connect(socketFd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
    if (nRet < 0){
        LOGE("socket %d. Failed to connect() :%s.\n", socketFd, strerror(errno));
        closesocket(socketFd);
        return false;
    }
    LOGD("socket %d, connect %s\n", socketFd, 0 == nRet ? "success .":"failure !");

    mSocketFd = socketFd;
    mIsConnected = true;
    return true;
}

void CSocketClient::closeTo() {
    close(mSocketFd);
    mSocketFd = -1;
    mIsConnected = false;
}

int CSocketClient::sendToServer(QOSCMD *msg) {

    if (!mIsConnected){
        if (!connectTo()){
            LOGE("connect to %s failed!\n", mHost);
        }
    }

    int ret = send(mSocketFd, (char *)msg, sizeof(QOSMSG), 0);
    if (ret <= 0){
        LOGE("send msg failed!\n");
        closeTo();
    }

    return ret;
}





