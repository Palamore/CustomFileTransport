
#pragma comment(lib, "ws2_32.lib")
#include "IncludeDefineNamespace.h"
#include "Send.h"
#include "Recv.h"

struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

Send::Network_Send sendObject;
Recv::Network_Recv recvObject;
bool exitFlag = false;
void RunListenThread();
void RunSendThread();
vector<string> Split(string targetStr, char splitter);


int main()
{
	WSADATA wsaData;
	// 윈속 버전을 2.2로 초기화
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	// TCP 소켓 생성
	sendObject.clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sendObject.clientSocket == INVALID_SOCKET) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "socket initialize success." << std::endl;

	// 접속할 서버 정보를 저장할 구조체
	SOCKADDR_IN stServerAddr;

	char	szOutMsg[MAX_BUFFER];
	char	sz_socketbuf_[MAX_BUFFER];
	stServerAddr.sin_family = AF_INET;
	// 접속할 서버 포트 및 IP
	stServerAddr.sin_port = htons(SERVER_PORT);
	//stServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	inet_pton(stServerAddr.sin_family, SERVER_IP, &stServerAddr.sin_addr.s_addr);

	nRet = connect(sendObject.clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	recvObject.clientSocket = sendObject.clientSocket;

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	std::cout << "Connection success..." << std::endl;

	t1.join();
	t2.join();
	closesocket(sendObject.clientSocket);
	std::cout << "Client has been terminated..." << std::endl;

	return 0;
}

void RunListenThread()
{
	char	sz_socketbuf_[MAX_BUFFER];
	

	while (1)
	{
		int nRecvLen = recv(sendObject.clientSocket, sz_socketbuf_, 1024, 0);
		if (nRecvLen == 0) {
			std::cout << "Server connection has been closed" << std::endl;
			closesocket(sendObject.clientSocket);
			return;
		}
		else if (nRecvLen == -1) {
			std::cout << "Error : " << WSAGetLastError() << std::endl;
			closesocket(sendObject.clientSocket);
			return;
		}

		if (!recvObject.OnRecvPacket(sz_socketbuf_))
		{
			exitFlag = true;
			cout << "ExitFlag set" << endl;
			break;
		}

		sz_socketbuf_[nRecvLen] = NULL;

	}
	cout << "ListenThread End" << endl;
}

void RunSendThread()
{
	char	szOutMsg[MAX_BUFFER];
	string outMsg;

	std::cout << "Nickname : ";
	std::cin >> sendObject.nickname;

	sendObject.SendLoginRequest("");

	while (!exitFlag) {
		std::cout << ">>";
		std::cin.getline(szOutMsg, MAX_BUFFER);
		if (exitFlag) break;
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
				sendObject.SendChatWhisper(splitted[INPUT_TARGET_NICKNAME_INDEX], msg);
				break;
			case 'l':
				sendObject.SendUserListRequest(" ");
				break;
			case 'e':
				sendObject.SendExitRequest(" ");
				exitFlag = true;
				break;
			case 'f':
				sendObject.SendFileSendRequest(splitted[INPUT_FILENAME_INDEX]);
				break;
			default:
				break;
			}
		}
		else
		{
			sendObject.SendChatNormal(szOutMsg);
		}
	}
	cout << "SendThread End" << endl;
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