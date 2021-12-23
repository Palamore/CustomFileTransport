//√‚√≥ : https://github.com/LimSungMin/IOCompletionPort
#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>
using namespace std;

#define SERVER_PORT 4000
#define BUFFER_LENGTH 1024
#define SERVER_IP "127.0.0.1"

typedef struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[BUFFER_LENGTH];
	int				recvLength;
	int				sendLength;
};


class IOCompletionPort
{
public:
	IOCompletionPort();
	~IOCompletionPort();

	bool Initialize();

	void StartServer();

	bool CreateThread();

	void Thread();

private:
	stSOCKETINFO* m_pSocketInfo;
	SOCKET		  m_listenSocket;
	HANDLE		  m_hIOCP;
	bool		  m_bAccept;
	bool		  m_bThread;
	HANDLE*		  m_pHandle;
};
