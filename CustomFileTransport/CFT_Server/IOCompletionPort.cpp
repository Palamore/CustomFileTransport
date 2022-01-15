#include "IOCompletionPort.h"
#include "Debug.h"
#include <process.h>

bool Contain(vector<SOCKET*>& target, SOCKET value);

//string GetCurrentDay()
//{
//	time_t timer = time(NULL);
//	struct tm t; 
//	localtime_s(&t, &timer);
//	string year = to_string(t.tm_year + 1900);
//	int mon = t.tm_mon + 1;
//	string month = "";
//	if (mon < 10)
//	{
//		month = "0" + to_string(mon);
//	}
//	else
//	{
//		month = to_string(mon);
//	}
//	int da = t.tm_mday;
//	string day = "";
//	if (da < 10)
//	{
//		day = "0" + to_string(da);
//	}
//	else
//	{
//		day = to_string(da);
//	}
//	return (year + "_" + month + "_" + day);
//}

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	IOCompletionPort* pOverlappedEvent = (IOCompletionPort*)p;
	pOverlappedEvent->WorkerThread();
	return 0;
}

bool IOCompletionPort::BroadcastPacket(stSOCKETINFO* socketInfo, string serializedMsg) // ����� Ŭ��(���� Room ����) ��ü�� ����
{
	int		nResult = 0;
	DWORD	dwFlags = 0;
	DWORD	sendBytes = 0;

	socketInfo->dataBuf.buf = (CHAR*)(serializedMsg.c_str());
	socketInfo->dataBuf.len = serializedMsg.length();
	for (int i = 0; i < connectedClients->size(); i++)
	{
		nResult = WSASend(
			*(connectedClients->at(i)),
			&(socketInfo->dataBuf),
			1,
			&sendBytes,
			dwFlags,
			null,
			null
		);
		if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
			return false;
		}
		
	}
	Debug::Log("[BroadcastPacket] " + serializedMsg);
	return true;
}

bool IOCompletionPort::SendPacket(stSOCKETINFO* socketInfo, SOCKET target, string serializedMsg) // target Ŭ�� ���� : �۽���, �����ڰ� �ٸ�
{
	int		nResult = 0;
	DWORD	dwFlags = 0;
	DWORD	sendBytes = 0;

	socketInfo->dataBuf.buf = (CHAR*)(serializedMsg.c_str());
	socketInfo->dataBuf.len = serializedMsg.length();
	nResult = WSASend(
		target,
		&(socketInfo->dataBuf),
		1,
		&sendBytes,
		dwFlags,
		null,
		null
	);
	if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
	{
		Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
		return false;
	}
	Debug::Log("[SendPacket] " + serializedMsg);
	return true;
}

bool IOCompletionPort::ReplyPacket(stSOCKETINFO* socketInfo, string serializedMsg) // ��û�� ���´� Ŭ�� ���� : �۽���, �����ڰ� ����
{
	int		nResult = 0;
	DWORD	dwFlags = 0;
	DWORD	sendBytes = 0;

	socketInfo->dataBuf.buf = (CHAR*)(serializedMsg.c_str());
	socketInfo->dataBuf.len = serializedMsg.length();
	nResult = WSASend(
		socketInfo->socket,
		&(socketInfo->dataBuf),
		1,
		&sendBytes,
		dwFlags,
		null,
		null
	);
	if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
	{
		Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
		return false;
	}
	Debug::Log("[ReplyPacket] " + serializedMsg);
	return true;
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

	//while (!loggingStream->empty())
	//{
	//	delete loggingStream->back();
	//	loggingStream->pop_back();
	//}
	//delete loggingStream;

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
			Debug::LogError("socket(" + to_string(pSocketInfo->socket) + ") Disconnected\n");
			string nickname = "";
			for (int i = 0; i < clientInfoContainer->size(); i++)
			{
				if (pSocketInfo->socket == clientInfoContainer->at(i)->socket())
				{
					nickname = clientInfoContainer->at(i)->nickname();
				}
			}
			LoginRequest loginData;
			loginData.set_nickname(nickname);
			loginData.set_password("");

			OnRcvExitRequest(pSocketInfo, loginData.SerializeAsString());

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
			PacketMsg msg;
			msg.ParseFromString(string(pSocketInfo->dataBuf.buf));
			Debug::Log("Packet Recv : " + msg.SerializeAsString());

			switch (msg.type())
			{
			case PacketType::LOGIN_REQUEST:
				OnRcvLoginRequest(pSocketInfo, msg.data());
				break;
			case PacketType::CHAT_NORMAL:
				OnRcvChatNormal(pSocketInfo, msg.data(), msg.nickname());
				break;
			case PacketType::CHAT_WHISPER:
				OnRcvChatWhisper(pSocketInfo, msg.data(), msg.nickname());
				break;
			case PacketType::USER_LIST_REQUEST:
				OnRcvUserListRequest(pSocketInfo, msg.data());
				break;
			case PacketType::FILE_SEND_REQUEST:
				OnRcvFileSendRequest(pSocketInfo, msg.data());
				break;
			case PacketType::FILE_SEND_REQUEST_ANSWER:
				OnRcvAnsFileSendRequest(pSocketInfo, msg.data());
				break;
			case PacketType::EXIT_REQUEST:
				OnRcvExitRequest(pSocketInfo, msg.data());
				break;
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


void IOCompletionPort::OnRcvLoginRequest(stSOCKETINFO* socketInfo, string data)
{
	LoginRequest loginData;
	if (!loginData.ParseFromString(data))
	{
		Debug::LogError("ChatData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvLoginRequest] " + loginData.SerializeAsString());
	
	bool isSuccess = false;

	if (!Contain(*connectedClients, socketInfo->socket))
	{
		connectedClients->push_back(&socketInfo->socket);
		ClientInfo* cInfo = new ClientInfo();
		cInfo->set_socket(socketInfo->socket);
		cInfo->set_nickname(loginData.nickname());
		clientInfoContainer->push_back(cInfo);
		isSuccess = true;
	}

	AnsLoginRequest ansData;
	ansData.set_nickname(loginData.nickname());
	if (isSuccess)
	{
		ansData.set_type(LoginResultType::LOGIN_SUCCESS);

		/*int dirExist = 0;
		dirExist = _access(loginData.nickname().c_str(), 0);
		if (dirExist != 0)
		{
			int makeDir = 0;
			makeDir = _mkdir(loginData.nickname().c_str());
		}

		string logFileStr = loginData.nickname() + "/" + GetCurrentDay() + ".txt";
		dirExist = _access(logFileStr.c_str(), 0);
		if (dirExist != 0)
		{
			ofstream makeFile(logFileStr.c_str());
			makeFile.close();
		}*/
		//ofstream* fileStream = new ofstream(logFileStr.c_str());
		//loggingStream->push_back(fileStream);

	}
	else
	{
		ansData.set_type(LoginResultType::LOGIN_FAIL);
	}
	SendAnsLoginRequest(socketInfo, ansData);
}
void IOCompletionPort::OnRcvChatNormal(stSOCKETINFO* socketInfo, string data, string nickname)
{
	ChatNormal chatData;
	if (!chatData.ParseFromString(data))
	{
		Debug::LogError("ChatData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvChatNormal] " + chatData.SerializeAsString());

	AnsChatNormal ansData;
	ansData.set_data(chatData.data());
	ansData.set_nickname(nickname);

	SendAnsChatNormal(socketInfo, ansData);
}
void IOCompletionPort::OnRcvChatWhisper(stSOCKETINFO* socketInfo, string data, string nickname)
{
	ChatWhisper chatData;
	if (!chatData.ParseFromString(data))
	{
		Debug::LogError("ChatData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvChatWhisper] " + chatData.SerializeAsString());

	string targetNickname = "";
	int targetClientIndex = -1;
	SOCKET targetSocket = NULL;
	
	for (int i = 0; i < clientInfoContainer->size(); i++)
	{
		if (clientInfoContainer->at(i)->nickname() == chatData.targetnickname())
		{
			targetNickname = chatData.targetnickname();
			targetClientIndex = i;
			targetSocket = clientInfoContainer->at(i)->socket();
		}
	}

	if (targetClientIndex == -1)
	{
		AnsRequestFail failData;
		failData.set_data("Nickname " + chatData.targetnickname() + " does not exist in room.");

		SendAnsRequestFail(socketInfo, failData);
		return;
	}

	AnsChatWhisper ansData;
	ansData.set_data(chatData.data());
	ansData.set_nickname(nickname);
	ansData.set_targetnickname(chatData.targetnickname());

	SendAnsChatWhisper(socketInfo, targetSocket, ansData);
}

void IOCompletionPort::OnRcvUserListRequest(stSOCKETINFO* socketInfo, string data)
{
	UserListRequest listData;
	if (!listData.ParseFromString(data))
	{
		Debug::LogError("ListData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvUserListRequest] " + listData.SerializeAsString());

	AnsUserListRequest ansData;
	for (int i = 0; i < clientInfoContainer->size(); i++)
	{
		ansData.add_data(clientInfoContainer->at(i)->nickname());
	}

	SendAnsUserListRequest(socketInfo, ansData);
}

void IOCompletionPort::OnRcvFileSendRequest(stSOCKETINFO* socketInfo, string data)
{
	FileSendRequest fileData;
	if (!fileData.ParseFromString(data))
	{
		Debug::LogError("fileData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvFileSendRequest] " + fileData.SerializeAsString());


	// TODO :: ��Ÿ���� Parser �����ߵ�
	ofstream metaFile(METAFILE_PATH);
	metaFile << fileData.filename();
	metaFile.close();

	ShellExecute(NULL, TEXT("open"), TEXT(UDP_SERVER_PATH), NULL, NULL, SW_SHOW);

	AnsFileSendRequest ansData;
	ansData.set_data("true");
	// ������ �ʿ� Answer ��Ŷ ����
	SendAnsFileSendRequest(socketInfo, ansData);
}

void IOCompletionPort::OnRcvAnsFileSendRequest(stSOCKETINFO* socketInfo, string data)
{
	AnsFileSendRequest fileData;
	if (!fileData.ParseFromString(data))
	{
		Debug::LogError("fileData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvAnsFileSendRequest] " + fileData.SerializeAsString());

	// TODO :: ������ �� UDP �������� ����.
	// https://3001ssw.tistory.com/71

}



void IOCompletionPort::OnRcvExitRequest(stSOCKETINFO* socketInfo, string data)
{
	ExitRequest exitReq;
	if (!exitReq.ParseFromString(data))
	{
		Debug::LogError("exitReqData Parsing Failed");
		return;
	}
	Debug::Log("[OnRcvExitRequest] " + exitReq.SerializeAsString());

	int		nResult = 0;
	DWORD	dwFlags = 0;
	DWORD	sendBytes = 0;

	int targetClientIndex = -1;
	string exitedNickname = "";
	for (int i = 0; i < clientInfoContainer->size(); i++)
	{
		if (socketInfo->socket == clientInfoContainer->at(i)->socket())
		{
			targetClientIndex = i;
			exitedNickname = clientInfoContainer->at(i)->nickname();
		}
	}
	if (clientInfoContainer->size() == 0) return;

	switch (exitReq.type())
	{
	case EXIT_NORMAL:
		clientInfoContainer->erase(clientInfoContainer->begin() + targetClientIndex);
		connectedClients->erase(connectedClients->begin() + targetClientIndex);
		break;
	case EXIT_DESTRUCTOR:
		clientInfoContainer->erase(clientInfoContainer->begin() + targetClientIndex);
		connectedClients->erase(connectedClients->begin() + targetClientIndex);
		break;
	}

	string msg(exitedNickname + " has left.");

	AnsExitRequest ansData;
	ansData.set_type(ExitType::EXIT_NORMAL);
	ansData.set_data(msg);

	SendAnsExitRequest(socketInfo, ansData);
}

void IOCompletionPort::SendAnsLoginRequest(stSOCKETINFO* socketInfo, AnsLoginRequest loginData)
{
	PacketMsg msg;
	msg.set_type(PacketType::LOGIN_REQUEST);
	msg.set_data(loginData.SerializeAsString());

	string serializedMsg = msg.SerializeAsString();

	if (ReplyPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsLoginRequest] " + loginData.SerializeAsString());
	}
}

void IOCompletionPort::SendAnsRequestFail(stSOCKETINFO* socketInfo, AnsRequestFail failData)
{
	PacketMsg msg;
	msg.set_type(PacketType::REQUEST_FAIL);
	msg.set_data(failData.SerializeAsString());
	
	string serializedMsg = msg.SerializeAsString();

	if (ReplyPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsRequestFail] " + failData.SerializeAsString());
	}
}

void IOCompletionPort::SendAnsChatNormal(stSOCKETINFO* socketInfo, AnsChatNormal chatData)
{
	PacketMsg msg;
	msg.set_type(PacketType::CHAT_NORMAL);
	msg.set_data(chatData.SerializeAsString());

	string serializedMsg = msg.SerializeAsString();

	if (BroadcastPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsChatNormal] " + chatData.SerializeAsString());
	}
}

void IOCompletionPort::SendAnsChatWhisper(stSOCKETINFO* socketInfo, SOCKET target, AnsChatWhisper chatData)
{
	PacketMsg msg;
	msg.set_type(PacketType::CHAT_WHISPER);
	msg.set_data(chatData.SerializeAsString());

	string serializedMsg = msg.SerializeAsString();

	if (SendPacket(socketInfo, target, serializedMsg))
	{
		Debug::Log("[SendAnsChatWhisper] " + chatData.SerializeAsString());
	}
}

void IOCompletionPort::SendAnsUserListRequest(stSOCKETINFO* socketInfo, AnsUserListRequest listData)
{
	PacketMsg msg;
	msg.set_type(PacketType::USER_LIST_REQUEST);
	msg.set_data(listData.SerializeAsString());

	string serializedMsg = msg.SerializeAsString();

	if (ReplyPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsUserListRequest]" + listData.SerializeAsString());
	}
}

void IOCompletionPort::SendFileSendRequest(stSOCKETINFO* socketInfo, string fileName)
{
	ifstream openFile(fileName, ios::binary);
	int length;
	//char* buffer;
	openFile.seekg(0, ios::end);
	length = openFile.tellg();
	openFile.seekg(0, ios::beg);
	//buffer = new char[length];
	//openFile.read(buffer, length);
	openFile.close();

	FileSendRequest fileData;
	fileData.set_filename(fileName);
	fileData.set_filesize(length);

	PacketMsg msg;
	msg.set_type(PacketType::FILE_SEND_REQUEST);
	msg.set_data(fileData.SerializeAsString());

	// TODO:: ���� ��� ������ �޾ƾ���.

}

void IOCompletionPort::SendAnsFileSendRequest(stSOCKETINFO* socketInfo, AnsFileSendRequest fileData)
{
	PacketMsg msg;
	msg.set_type(PacketType::FILE_SEND_REQUEST_ANSWER);
	msg.set_data(fileData.SerializeAsString());
	string serializedMsg = msg.SerializeAsString();

	if (ReplyPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsFileSendRequest]" + fileData.SerializeAsString());
	}
}


void IOCompletionPort::SendAnsExitRequest(stSOCKETINFO* socketInfo, AnsExitRequest exitData)
{
	PacketMsg msg;
	msg.set_type(PacketType::EXIT_REQUEST);
	msg.set_data(exitData.SerializeAsString());

	string serializedMsg = msg.SerializeAsString();

	if (BroadcastPacket(socketInfo, serializedMsg))
	{
		Debug::Log("[SendAnsExitRequest] " + exitData.SerializeAsString());
	}
}
