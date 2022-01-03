
#pragma comment(lib, "ws2_32.lib")
#include "IncludeDefineNamespace.h"


struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

Network_Send send;

void RunListenThread();
void RunSendThread();
vector<string> Split(string targetStr, char splitter);


int main()
{
	WSADATA wsaData;
	// ���� ������ 2.2�� �ʱ�ȭ
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	// TCP ���� ����
	send.clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (send.clientSocket == INVALID_SOCKET) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "socket initialize success." << std::endl;

	// ������ ���� ������ ������ ����ü
	SOCKADDR_IN stServerAddr;

	char	szOutMsg[MAX_BUFFER];
	char	sz_socketbuf_[MAX_BUFFER];
	stServerAddr.sin_family = AF_INET;
	// ������ ���� ��Ʈ �� IP
	stServerAddr.sin_port = htons(SERVER_PORT);
	//stServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	inet_pton(stServerAddr.sin_family, SERVER_IP, &stServerAddr.sin_addr.s_addr);

	nRet = connect(send.clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	std::cout << "Connection success..." << std::endl;
	while (true) {


	}

	t1.join();
	t2.join();
	closesocket(send.clientSocket);
	std::cout << "Client has been terminated..." << std::endl;

	return 0;
}

void RunListenThread()
{
	char	sz_socketbuf_[MAX_BUFFER];
	while (1)
	{
		int nRecvLen = recv(send.clientSocket, sz_socketbuf_, 1024, 0);
		if (nRecvLen == 0) {
			std::cout << "Server connection has been closed" << std::endl;
			closesocket(send.clientSocket);
			return;
		}
		else if (nRecvLen == -1) {
			std::cout << "Error : " << WSAGetLastError() << std::endl;
			closesocket(send.clientSocket);
			return;
		}

		sz_socketbuf_[nRecvLen] = NULL;
		std::cout << "Message received : bytes[" << nRecvLen << "], message : [" <<
			sz_socketbuf_ << "]" << std::endl;
	}
}

void RunSendThread()
{
	char	szOutMsg[MAX_BUFFER];
	string outMsg;

	std::cout << "Nickname : ";
	std::cin >> send.nickname;

	send.SendLoginRequest("");

	while (true) {
		std::cout << ">>";
		std::cin.getline(szOutMsg, MAX_BUFFER);

		if (szOutMsg[INPUT_COMMAND_INDEX] == '/')
		{
			vector<string> splitted;
			splitted = Split(szOutMsg, ' ');
			string msg = "";
			switch (splitted[INPUT_COMMAND_INDEX][INPUT_COMMAND_TYPE_INDEX])
			{
			case 'w':
				for (int i = 2; i < splitted.size(); i++)
				{
					msg += splitted[i] + " ";
				}
				send.SendChatWhisper(splitted[INPUT_TARGET_NICKNAME_INDEX], msg);
				break;
			case 'l':
				send.SendRoomListRequest(splitted[INPUT_MESSAGE_INDEX]);
				break;
			case 'e':
				send.SendExitRequest(splitted[INPUT_MESSAGE_INDEX]);
				exit(0);
				break;
			default:
				break;
			}
		}
		send.SendChatNormal(szOutMsg);
	}
}

vector<string> Split(string targetStr, char splitter)
{
	vector<string> vect;
	string e = "";
	for (int i = 0; i < targetStr.size(); i++)
	{
		if (targetStr[i] == splitter)
		{
			vect.push_back(e);
			e = "";
		}
		else
		{
			e += targetStr[i];
		}
	}
	vect.push_back(e);
	return vect;
}