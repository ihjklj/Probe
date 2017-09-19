
#include "ihjkljSocketServer.h"
#include "ihjkljThread.h"
#include <asm/ioctls.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/system_properties.h>
#include "nativeUtil.h"

//extern void uploadData(const char* dType, const char* aType, const char* data);

CSocketServer::CSocketServer() {
	m_fdListen = -1;
	m_nStop = 0;
	m_hThread = NULL;
	m_javaVm = NULL;
	m_host = NULL;
	m_port = 0;
}

CSocketServer::CSocketServer(JavaVM *vm, char *host, int port) {
	m_fdListen = -1;
	m_nStop = 0;
	m_hThread = NULL;
	m_javaVm = vm;
	m_host = strdup(host);
	m_port = port;
}

CSocketServer::~CSocketServer() {
	m_nStop = 1;
	
	if (m_fdListen != -1){
		//不知道为什么有时候listen的socket在关闭后还会塞死，在这里先连接一下，以确保不会被塞死
		int fd = connectToServer("127.0.0.1", 13980);
		if (fd != -1)
			closesocket(fd);
		closesocket(m_fdListen);
		m_fdListen = -1;
	}
	
	if (m_hThread != NULL){
		delete (CThread *)m_hThread;
	}

	free(m_host);
	LOGD("%s leave.\n", __FUNCTION__);
}

void CSocketServer::init(JavaVM *vm, char *host, int port) {
	m_javaVm = vm;
	m_host = host;
	m_port = port;
}

void CSocketServer::start() {
	LOGD("Start.\n");
	if (m_hThread == NULL) {
		m_hThread = new CThread(m_javaVm, runThreadFunc, this);
	}
	
	/* 如果QOS没有启动就启动qos */
	//property_set("ctl.start", "IptvQosServ");
}

void CSocketServer::stop() {
	LOGD("Stop\n");
	
	/* 退出qos */
	//property_set("ctl.stop", "IptvQosServ");
}


int CSocketServer::connectToServer(const char* ip, int port) {
	
    int socketFd = socket(PF_INET, SOCK_STREAM, 0);
	if (socketFd == -1){
		LOGE("socket failed!\n");
		return -1;
	}

	struct sockaddr_in clientAddr; 
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(ip);
    clientAddr.sin_port = htons(port);
    
    struct timeval tv = {3, 0};

	/* 设置发送超时 */
    setsockopt(socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));

	/* 设置接收超时,因为加了线程锁所以这里设置接收超时就很有必要了 */
	setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
	
    int nRet = connect(socketFd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
    if (nRet < 0){
        LOGE("socket %d. Failed to connect() :%s.\n", socketFd, strerror(errno));
        closesocket(socketFd);
        return nRet;
    }
    LOGD("socket %d, connect %s\n", socketFd, 0 == nRet ? "success .":"failure !");
    return socketFd;
}

//调试端关闭了连接
void CSocketServer::onCloseManager(int fd) {
	
	vector<int>::iterator it;
	for (it = m_vecSocket.begin(); it != m_vecSocket.end(); it++){
		if (*it == fd){
			m_vecSocket.erase(it);
			break;
		}
	}
}

void CSocketServer::onUploadData(char* pBuffer) {
	char dType[64] = {0};
	char aType[64] = {0};
	if (sscanf(pBuffer, "%63[^|]|%63[^|]", dType, aType) == 2) {
		const char* data = pBuffer + (strlen(dType) + strlen(aType) + 2);
		LOGD("dType:%s,aType:%s\ndata:%s.\n", dType, aType, data);
		m_uploadFunc(dType, aType,  data);
	}
}

int CSocketServer::recvData(char* pBuffer, int fd, int len) {
	int nCnt = 0;
	while (nCnt < len){
		int nRet = recv(fd, pBuffer+nCnt, len-nCnt, 0);
		if (nRet > 0)
			nCnt += len;
	}
	return nCnt;
}

//接收管理端发来的数据
void CSocketServer::onCmdManager(int fd) {
	DATAMSG qos;
	int nRet = recv(fd, (char*)&qos, sizeof(DATAMSG), 0);
	//服务端关闭了连接
	if (nRet <= 0) {
		LOGD("socket is close:%d,%d\n", nRet, fd);
		onCloseManager(fd);
		return;
	}
	LOGD("cmd:%d, len:%d\n", qos.cmd, (int)qos.len);
	char* pBuffer = (char*)malloc(qos.len + 1);
	if (pBuffer == NULL) {
		LOGD("malloc faild:%d,%s\n", errno, strerror(errno));
		return;
	}
	nRet = recvData(pBuffer, fd, qos.len);
	pBuffer[nRet] = 0;
	switch (qos.cmd) {
		case Upload:
			onUploadData(pBuffer);
			break;
		default:
			break;
	}
	free(pBuffer);
}

void CSocketServer::run(){
	do {
		struct sockaddr_in RecvAddr;
		int nLen = sizeof(RecvAddr);
		int nReuseAddr = 1;
		int nRet = 0;
		memset(&RecvAddr, 0, sizeof(RecvAddr));

		RecvAddr.sin_family = AF_INET;
		RecvAddr.sin_port = htons(m_port);
		RecvAddr.sin_addr.s_addr = inet_addr(m_host);
		
		//创建用于监听调试方的连接的socket
		m_fdListen = socket(AF_INET, SOCK_STREAM, 0);
		
		//设置可重用地址
		setsockopt(m_fdListen, SOL_SOCKET, SO_REUSEADDR, (char *)&nReuseAddr, sizeof(nReuseAddr));
		
		//绑定到指定端口
		nRet = bind(m_fdListen, (struct sockaddr *)&RecvAddr, sizeof(RecvAddr));
		if (nRet == -1){
			LOGD("bind err:%d, %s.\n", errno, strerror(errno));
			closesocket(m_fdListen);
			Sleep(1000);
			continue;
		}
		LOGD("bind succeed.\n");
		
		//开始监听
		nRet = listen(m_fdListen, 10);
		if (nRet == -1){
			LOGD("listen err:%d, %s.\n", errno, strerror(errno));
			closesocket(m_fdListen);
			continue;
		}
		
		while (m_nStop == 0){
			fd_set fdr;
			FD_ZERO(&fdr);
			FD_SET(m_fdListen, &fdr);
			int fdmax = m_fdListen;
			for (int i=0;i<(int)m_vecSocket.size();i++){
				if (m_vecSocket[i] > fdmax)
					fdmax = m_vecSocket[i];
				FD_SET(m_vecSocket[i], &fdr);
			}
			
			/* 这里timeout传入NULL就是设置成阻塞模式，这样的处理那么返回之后里面判断
			m_nStop是否为1的处理就显得很有必要了 */
			nRet = select(fdmax+1, &fdr, NULL, NULL, NULL);
			
			/* 因为设置的select是阻塞模式，所以最安全的做法就是select返回以后立马判断
			一下是否退出标志已经被置位 */
			if (m_nStop == 1)
				break;
			
			/* 然后才是判断select返回的原因是什么 */
			if (nRet == -1)
				continue;
			
			//第３方连接
			if (FD_ISSET(m_fdListen, &fdr) > 0){
				int fd = accept(m_fdListen, NULL, NULL);
				if (fd != -1){
					m_vecSocket.push_back(fd);
					//m_vecSocket.add(fd);
					LOGD("%s socket:%d.\n", __FUNCTION__, fd);
				}
			}
			else {
				//调试命令
				for (int i=0; i<(int)m_vecSocket.size(); i++){
					if (FD_ISSET(m_vecSocket[i], &fdr) > 0){
						onCmdManager(m_vecSocket[i]);
					}
				}
			}
		}

	} while(m_nStop == 0);
	LOGD("%s leave.\n", __FUNCTION__);
}

int CSocketServer::runThreadFunc(void* lParam) {
	((CSocketServer*)lParam)->run();
	return 1;
}
