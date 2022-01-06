//원본 출처 : https://github.com/LimSungMin/IOCompletionPort
#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include "ProtocolTag.h"
#include "PacketTag.pb.h"
#include "ClientInfo.pb.h"
#include <WinSock2.h>
#include <memory>
using namespace ServerPacket;
using namespace std;
using namespace PacketTag;

#define	MAX_BUFFER		1024
#define SERVER_PORT		8000
#define MAX_CLIENT		1000
#define null			NULL

struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};


class IOCompletionPort
{
public:
	IOCompletionPort();
	~IOCompletionPort();

	// 소켓 등록 및 서버 정보 설정
	bool Initialize();
	// 서버 시작
	void StartServer();
	// 작업 스레드 생성
	bool CreateWorkerThread();
	// 작업 스레드
	void WorkerThread();

	bool BroadCastPacket(stSOCKETINFO* socketInfo, string serializedMsg);
	bool SendPacket(stSOCKETINFO* socketInfo, SOCKET target, string serializedMsg);
	bool ReplyPacket(stSOCKETINFO* socketInfo, string serializedMsg);

	void OnRcvLoginRequest(stSOCKETINFO* socketInfo, string data);
	void OnRcvChatNormal(stSOCKETINFO* socketInfo, string data, string nickname);
	void OnRcvChatWhisper(stSOCKETINFO* socketInfo, string data, string nickname);
	void OnRcvUserListRequest(stSOCKETINFO* socketInfo, string data);
	void OnRcvExitRequest(stSOCKETINFO* socketInfo, string data);

	void SendAnsLoginRequest(stSOCKETINFO* socketInfo, AnsLoginRequest loginData);
	void SendAnsChatNormal(stSOCKETINFO* socketInfo, AnsChatNormal chatData);
	void SendAnsChatWhisper(stSOCKETINFO* socketInfo, AnsChatWhisper chatData);
	void SendAnsUserListRequest(stSOCKETINFO* socketInfo, AnsUserListRequest listData);
	void SendAnsExitRequest(stSOCKETINFO* socketInfo, AnsExitRequest exitData);

	vector<SOCKET*>* connectedClients;
	vector<ClientInfo*>* clientInfoContainer;

private:
	stSOCKETINFO* m_pSocketInfo;		// 소켓 정보
	SOCKET			m_listenSocket;		// 서버 리슨 소켓
	HANDLE			m_hIOCP;			// IOCP 객체 핸들
	bool			m_bAccept;			// 요청 동작 플래그
	bool			m_bWorkerThread;	// 작업 스레드 동작 플래그
	HANDLE* m_pWorkerHandle;	// 작업 스레드 핸들
};
