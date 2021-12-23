//출처 : https://github.com/LimSungMin/IOCompletionPort
#include "IOCompletionPort.h"
#include <process.h>


int LogError(string str)
{
	cout << "ERROR : " + str + "\n" << endl;
	return -1;
}

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	IOCompletionPort* pOverlappedEvent = (IOCompletionPort*)p;
	pOverlappedEvent->Thread();
	return 0;
}

IOCompletionPort::IOCompletionPort()
	: m_pSocketInfo(NULL),
	m_listenSocket(NULL),
	m_hIOCP(NULL),
	m_bAccept(true),
	m_bThread(true),
	m_pHandle(NULL)
{}

IOCompletionPort::~IOCompletionPort()
{
	WSACleanup();

	if (m_pSocketInfo != NULL)
	{
		delete[] m_pSocketInfo;
		m_pSocketInfo = NULL;
	}

	if (m_pHandle != NULL)
	{
		delete[] m_pHandle;
		m_pHandle = NULL;
	}
}

bool IOCompletionPort::Initialize()
{
	WSADATA wsaData;
	int nResult;

	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nResult != 0)
	{
		LogError("Winsock Init Failed");
		return false;
	}

	m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_listenSocket == INVALID_SOCKET)
	{
		LogError("Socket Create Failed");
		return false;
	}

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	nResult = bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
	if (nResult == SOCKET_ERROR)
	{
		LogError("Bind Failed");
		closesocket(m_listenSocket);
		WSACleanup();
		return false;
	}

	nResult = listen(m_listenSocket, 5);
	if (nResult == SOCKET_ERROR)
	{
		LogError("Listen Failed");
		closesocket(m_listenSocket);
		WSACleanup();
		return false;
	}

	return true;
}

void IOCompletionPort::StartServer()
{
	int nResult;
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvLength;
	DWORD flags;
	


	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (!CreateThread()) return;

	cout << "Server Starting...." << endl;

	while (m_bAccept)
	{
		clientSocket = WSAAccept(
			m_listenSocket, (sockaddr*)&clientAddr, &addrLen, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			LogError("Aceept Failed");
			return;
		}

		m_pSocketInfo = new stSOCKETINFO();
		m_pSocketInfo->socket = clientSocket;
		m_pSocketInfo->recvLength = 0;
		m_pSocketInfo->sendLength = 0;
		m_pSocketInfo->dataBuf.len = BUFFER_LENGTH;
		m_pSocketInfo->dataBuf.buf = m_pSocketInfo->messageBuffer;
		flags = 0;

		m_hIOCP = CreateIoCompletionPort((HANDLE)clientSocket, m_hIOCP, (DWORD)m_pSocketInfo, 0);

		nResult = WSARecv(
			m_pSocketInfo->socket,
			&m_pSocketInfo->dataBuf,
			1,
			&recvLength,
			&flags,
			&(m_pSocketInfo->overlapped),
			NULL
		);

		if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			int error = WSAGetLastError();
			LogError("IO Pending Failed : " + to_string(error));
			return;
		}

	}

}

bool IOCompletionPort::CreateThread()
{
	unsigned int threadId;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	cout << "CPU Count : " + to_string(sysInfo.dwNumberOfProcessors) << endl;
	int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;

	m_pHandle = new HANDLE[nThreadCnt];

	for (int i = 0; i < nThreadCnt; i++)
	{
		m_pHandle[i] = (HANDLE*)_beginthreadex(
			NULL, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &threadId
		);
		if (m_pHandle[i] == NULL)
		{
			LogError("Worker Thread Creating Failed");
			return false;
		}
		ResumeThread(m_pHandle[i]);
	}
	cout << "Worker Thread Started..." << endl;
	return true;
}

void IOCompletionPort::Thread()
{
	BOOL bResult;
	int	nResult;

	DWORD recvLength;
	DWORD sendLength;

	stSOCKETINFO* pCompletionKey;
	stSOCKETINFO* pSocketInfo;

	DWORD dwFlags = 0;

	while (m_bThread)
	{
		bResult = GetQueuedCompletionStatus(m_hIOCP,
			&recvLength,
			(PULONG_PTR)&pCompletionKey,
			(LPOVERLAPPED*)&pSocketInfo,
			INFINITE);

		if (!bResult && recvLength == 0)
		{
			cout << "socket(" + to_string(pSocketInfo->socket) + ") Disconnected." << endl;
			closesocket(pSocketInfo->socket);
			free(pSocketInfo);
			continue;
		}

		pSocketInfo->dataBuf.len = recvLength;

		if (recvLength == 0)
		{
			closesocket(pSocketInfo->socket);
			free(pSocketInfo);
			continue;
		}
		else
		{
			cout << "Message Received - Bytes : " + to_string(pSocketInfo->dataBuf.len) + ", " << endl;
			cout << pSocketInfo->dataBuf.buf << endl;

			nResult = WSASend(
				pSocketInfo->socket,
				&(pSocketInfo->dataBuf),
				1,
				&sendLength,
				dwFlags,
				NULL,
				NULL
			);

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				LogError("WSASend Failed : " + to_string(WSAGetLastError()));
			}

			printf_s("[INFO] 메시지 송신 - Bytes : [%d], Msg : [%s]\n",
				pSocketInfo->dataBuf.len, pSocketInfo->dataBuf.buf);

			// stSOCKETINFO 데이터 초기화
			ZeroMemory(&(pSocketInfo->overlapped), sizeof(OVERLAPPED));
			pSocketInfo->dataBuf.len = BUFFER_LENGTH;
			pSocketInfo->dataBuf.buf = pSocketInfo->messageBuffer;
			ZeroMemory(pSocketInfo->messageBuffer, BUFFER_LENGTH);
			pSocketInfo->recvLength = 0;
			pSocketInfo->sendLength = 0;

			dwFlags = 0;

			// 클라이언트로부터 다시 응답을 받기 위해 WSARecv 를 호출해줌
			nResult = WSARecv(
				pSocketInfo->socket,
				&(pSocketInfo->dataBuf),
				1,
				&recvLength,
				&dwFlags,
				(LPWSAOVERLAPPED) & (pSocketInfo->overlapped),
				NULL
			);

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				LogError("WSARecv Failed : " + to_string(WSAGetLastError()));
			}
		}
		
	}

}
