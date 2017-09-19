
#ifndef __SOCKET_CMD__H__
#define __SOCKET_CMD__H__

#include "nativeUtil.h"
#include <vector>

//using namespace android;
using namespace std;

enum DataCmd {
	Upload = 0
};

typedef struct {
	enum DataCmd cmd;//命令值
	size_t len;//msg长度
} DATAMSG;

typedef struct {
	int enVidFrmType;  //视频帧类型
	int  nFrmSize;    //视频帧大小
	int  nMaxQP;      // 视频帧QP
	int  nMinQP;
	int	 nAvgQP;
	int  nMaxMV;       //最大MV
	int  nMinMV;        //最小MV
	int  nAvgMV;      //平均MV
	int  SkipRatio;   // MV=0的MB比例
	int	 decoderbuffer;
} VIDEO_FRAME_INFO;

class CSocketServer {
public:
	CSocketServer();
	CSocketServer(JavaVM* vm, char *host, int port);
	virtual ~CSocketServer();

	void init(JavaVM *vm, char *host, int port);
	void run();
	void start();
	void stop();
	void setListener(UPLOAD_FUNC uploadFunc) { m_uploadFunc = uploadFunc; }

protected:
	static int runThreadFunc(void* lParam);
	int connectToServer(const char* ip, int port);
	void onCloseManager(int fd);
	void onCmdManager(int fd);
	int recvData(char* pBuffer, int fd, int len);
	void onUploadData(char* pBuffer);

protected:
	int				m_port;
	int				m_nStop;
	int				m_fdListen;
	vector<int>		m_vecSocket;
	void*			m_hThread;
	char*			m_host;
	JavaVM*			m_javaVm;
	UPLOAD_FUNC 	m_uploadFunc;
};

#endif
