#include "IOCompletionPort.h"
#include "Debug.h"
#include <process.h>

void RemoveTag(char* buf, int length);
bool Contain(vector<SOCKET*>& target, SOCKET value);

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	IOCompletionPort* pOverlappedEvent = (IOCompletionPort*)p;
	pOverlappedEvent->WorkerThread();
	return 0;
}

IOCompletionPort::IOCompletionPort()
	:m_bWorkerThread(true)
	, m_bAccept(true)
	, connectedClients(new vector<SOCKET*>())
	, m_pSocketInfo(null)
	, m_listenSocket(0)
	, m_hIOCP(null)
	, m_pWorkerHandle(null)
	, clientInfoContainer(new vector<ClientInfo*>())
{
	connectedClients->reserve(MAX_CLIENT);
	clientInfoContainer->reserve(MAX_CLIENT);
}


IOCompletionPort::~IOCompletionPort()
{
	// winsock �� ����� ������
	WSACleanup();
	// �� ����� ��ü�� ����
	while (!connectedClients->empty())
	{
		delete connectedClients->back();
		connectedClients->pop_back();
	}
	delete connectedClients;

	while (!clientInfoContainer->empty())
	{
		delete clientInfoContainer->back();
		clientInfoContainer->pop_back();
	}
	delete clientInfoContainer;

	if (m_pSocketInfo)
	{
		delete[] m_pSocketInfo;
		m_pSocketInfo = null;
	}

	if (m_pWorkerHandle)
	{
		delete[] m_pWorkerHandle;
		m_pWorkerHandle = null;
	}
}

bool IOCompletionPort::Initialize()
{
	WSADATA wsaData;
	int nResult;
	// winsock 2.2 �������� �ʱ�ȭ
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		Debug::LogError("Winsock Initialize Failed\n");
		return false;
	}

	// ���� ����
	m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, null, 0, WSA_FLAG_OVERLAPPED);
	if (m_listenSocket == INVALID_SOCKET)
	{
		Debug::LogError("Socket Create Failed\n");
		return false;
	}

	// ���� ���� ����
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


	// ���� ����
	nResult = bind(m_listenSocket, (struct sockaddr*)&serverAddr, (int)sizeof(SOCKADDR_IN));
	if (nResult == SOCKET_ERROR)
	{
		Debug::LogError("Listen Failed\n");
		closesocket(m_listenSocket);
		WSACleanup();
		return false;
	}

	// ���� ��⿭ ����
	nResult = listen(m_listenSocket, 5);
	if (nResult == SOCKET_ERROR)
	{
		Debug::LogError("Listen Failed\n");
		closesocket(m_listenSocket);
		WSACleanup();
		return false;
	}

	return true;
}

void IOCompletionPort::StartServer()
{
	int nResult;
	// Ŭ���̾�Ʈ ����
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvBytes;
	DWORD flags;

	// Completion Port ��ü ����
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, null, 0, 0);

	// Worker Thread ����
	if (!CreateWorkerThread()) return;

	Debug::Log("Server Start...\n");

	// Ŭ���̾�Ʈ ������ ����
	while (m_bAccept)
	{
		clientSocket = WSAAccept(
			m_listenSocket, (struct sockaddr*)&clientAddr, &addrLen, null, null
		);

		if (clientSocket == INVALID_SOCKET)
		{
			Debug::LogError("Accept Failed\n");
			return;
		}

		m_pSocketInfo = new stSOCKETINFO();
		m_pSocketInfo->socket = clientSocket;
		m_pSocketInfo->recvBytes = 0;
		m_pSocketInfo->sendBytes = 0;
		m_pSocketInfo->dataBuf.len = MAX_BUFFER;
		m_pSocketInfo->dataBuf.buf = m_pSocketInfo->messageBuffer;
		flags = 0;

		m_hIOCP = CreateIoCompletionPort(
			(HANDLE)clientSocket, m_hIOCP, (DWORD)m_pSocketInfo, 0
		);

		// ��ø ������ �����ϰ� �Ϸ�� ����� �Լ��� �Ѱ���
		nResult = WSARecv(
			m_pSocketInfo->socket,
			&m_pSocketInfo->dataBuf,
			1,
			&recvBytes,
			&flags,
			&(m_pSocketInfo->overlapped),
			NULL
		);

		if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			Debug::LogError("IO Pending Failed : " + to_string(WSAGetLastError()));
			return;
		}
		if (!Contain(*connectedClients, m_pSocketInfo->socket))
		{
			connectedClients->push_back(&m_pSocketInfo->socket);
			ClientInfo* cInfo = new ClientInfo();
			cInfo->set_socket(m_pSocketInfo->socket);
			cInfo->set_nickname(to_string(m_pSocketInfo->socket));
			clientInfoContainer->push_back(cInfo);
		}

	}

}
bool Contain(vector<SOCKET*>& target, SOCKET value)
{
	for (int i = 0; i < target.size(); i++)
	{
		if ((int)(*target.at(i)) == (int)value) return true;
	}
	return false;
}

bool IOCompletionPort::CreateWorkerThread()
{
	unsigned int threadId;
	// �ý��� ���� ������
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	Debug::Log("CPU Count : " + to_string(sysInfo.dwNumberOfProcessors) + "\n");
	// ������ �۾� �������� ������ (CPU * 2) + 1
	int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;

	// thread handler ����
	m_pWorkerHandle = new HANDLE[nThreadCnt];
	// thread ����
	for (int i = 0; i < nThreadCnt; i++)
	{
		m_pWorkerHandle[i] = (HANDLE*)_beginthreadex(
			null, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &threadId
		);
		if (m_pWorkerHandle[i] == null)
		{
			Debug::LogError("Worker Thread Create Failed\n");
			return false;
		}
		ResumeThread(m_pWorkerHandle[i]);
	}
	Debug::Log("Worker Thread Start...\n");
	return true;
}

void IOCompletionPort::WorkerThread()
{
	// �Լ� ȣ�� ���� ����
	BOOL	bResult;
	int		nResult;
	// Overlapped I/O �۾����� ���۵� ������ ũ��
	DWORD	recvBytes;
	DWORD	sendBytes;
	// Completion Key�� ���� ������ ����
	stSOCKETINFO* pCompletionKey;
	// I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������	
	stSOCKETINFO* pSocketInfo;
	// 
	DWORD	dwFlags = 0;

	while (m_bWorkerThread)
	{
		/**
		 * �� �Լ��� ���� ��������� WaitingThread Queue �� �����·� ���� ��
		 * �Ϸ�� Overlapped I/O �۾��� �߻��ϸ� IOCP Queue ���� �Ϸ�� �۾��� ������
		 * ��ó���� ��
		 */
		bResult = GetQueuedCompletionStatus(m_hIOCP,
			&recvBytes,				// ������ ���۵� ����Ʈ
			(PULONG_PTR)&pCompletionKey,	// completion key
			(LPOVERLAPPED*)&pSocketInfo,			// overlapped I/O ��ü
			INFINITE				// ����� �ð�
		);

		if (!bResult && recvBytes == 0)
		{
			Debug::Log("socket(" + to_string(pSocketInfo->socket) + ") ���� ����\n");
			closesocket(pSocketInfo->socket);
			free(pSocketInfo);
			continue;
		}

		pSocketInfo->dataBuf.len = recvBytes;

		if (recvBytes == 0)
		{
			closesocket(pSocketInfo->socket);
			free(pSocketInfo);
			continue;
		}
		else
		{
			Debug::Log("Msg Recv : " + string(pSocketInfo->dataBuf.buf) + "\n");

			/*string tag = "";
			tag += pSocketInfo->dataBuf.buf[0];
			tag += pSocketInfo->dataBuf.buf[1];
			tag += pSocketInfo->dataBuf.buf[2];
			
			RemoveTag(pSocketInfo->dataBuf.buf, pSocketInfo->dataBuf.len);*/

			ClientInfo rcvInfo;
			rcvInfo.ParseFromString(string(pSocketInfo->dataBuf.buf));

			for (int i = 0; i < clientInfoContainer->size(); i++)
			{
				if (pSocketInfo->socket == clientInfoContainer->at(i)->socket())
				{
					cout << clientInfoContainer->at(i)->nickname() << " Sent Msg " << endl;
				}
			}

			for (int i = 0; i < connectedClients->size(); i++)
			{
				nResult = WSASend(
					*(connectedClients->at(i)),
					&(pSocketInfo->dataBuf),
					1,
					&sendBytes,
					dwFlags,
					null,
					null
				);

				if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
				{
					Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
				}

				Debug::Log("Msg Sent : " + string(pSocketInfo->dataBuf.buf) + "\n");

			}
			// stSOCKETINFO ������ �ʱ�ȭ
			ZeroMemory(&(pSocketInfo->overlapped), sizeof(OVERLAPPED));
			pSocketInfo->dataBuf.len = MAX_BUFFER;
			pSocketInfo->dataBuf.buf = pSocketInfo->messageBuffer;
			ZeroMemory(pSocketInfo->messageBuffer, MAX_BUFFER);
			pSocketInfo->recvBytes = 0;
			pSocketInfo->sendBytes = 0;

			dwFlags = 0;

			// Ŭ���̾�Ʈ�κ��� �ٽ� ������ �ޱ� ���� WSARecv �� ȣ������
			nResult = WSARecv(
				pSocketInfo->socket,
				&(pSocketInfo->dataBuf),
				1,
				&recvBytes,
				&dwFlags,
				(LPWSAOVERLAPPED) & (pSocketInfo->overlapped),
				NULL
			);

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				Debug::LogError("WSARecv Failed : " + to_string(WSAGetLastError()));
			}
		}
	}
}

void RemoveTag(char* buf, int length)
{
	for (int i = 0; i < length - 4; i++)
	{
		buf[i] = buf[i + 4];
	}
	for (int i = length - 4; i < length; i++)
	{
		buf[i] = '\0';
	}
}