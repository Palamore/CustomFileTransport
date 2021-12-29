
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <string>
#include "ProtocolTag.h"
#include "ClientInfo.pb.h"
#include "PacketTag.pb.h"

using namespace ServerPacket;
using namespace PacketTag;
using namespace std;
#define	MAX_BUFFER		1024
#define SERVER_PORT		8000
#define SERVER_IP		"127.0.0.1"

struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

vector<ProtocolTag> AllTag;

void Init();

void RunListenThread(SOCKET clientSocket);

void RunSendThread(SOCKET clientSocket);

bool ValidateMessage(char* msg);

void AddTag(char* msg);

int main()
{
	Init();
	WSADATA wsaData;
	// 윈속 버전을 2.2로 초기화
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	// TCP 소켓 생성
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
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

	nRet = connect(clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	std::thread t1(RunListenThread, clientSocket);
	std::thread t2(RunSendThread, clientSocket);

	std::cout << "Connection success..." << std::endl;
	while (true) {


	}

	t1.join();
	t2.join();
	closesocket(clientSocket);
	std::cout << "Client has been terminated..." << std::endl;

	return 0;
}

void RunListenThread(SOCKET clientSocket)
{
	char	sz_socketbuf_[MAX_BUFFER];
	while (1)
	{
		int nRecvLen = recv(clientSocket, sz_socketbuf_, 1024, 0);
		if (nRecvLen == 0) {
			std::cout << "Client connection has been closed" << std::endl;
			closesocket(clientSocket);
			return;
		}
		else if (nRecvLen == -1) {
			std::cout << "Error : " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			return;
		}

		sz_socketbuf_[nRecvLen] = NULL;
		std::cout << "Message received : bytes[" << nRecvLen << "], message : [" <<
			sz_socketbuf_ << "]" << std::endl;
	}
}

void RunSendThread(SOCKET clientSocket)
{
	char	szOutMsg[MAX_BUFFER];
	string outMsg;
	while (true) {
		std::cout << ">>";
		std::cin.getline(szOutMsg, MAX_BUFFER);
		if (_strcmpi(szOutMsg, "quit") == 0) break;

		if (!ValidateMessage(szOutMsg))
		{
			AddTag(szOutMsg);
		}

		ClientInfo cInfo;
		cInfo.set_socket(333);
		cInfo.set_nickname("palamore");
		
		outMsg = cInfo.SerializeAsString();


		int nSendLen = send(clientSocket, outMsg.c_str(), strlen(outMsg.c_str()), 0);

		if (nSendLen == -1) {
			std::cout << "Error : " << WSAGetLastError() << std::endl;
			return;
		}

		std::cout << "Message sended : bytes[" << nSendLen << "], message : [" <<
			szOutMsg << "]" << std::endl << "outMSg : " << outMsg << std::endl;

	}
}


void Init()
{
	AllTag.reserve(100);
	AllTag.push_back(ProtocolTag::CHAT_NORMAL);
	AllTag.push_back(ProtocolTag::CHAT_WHISPER);
	AllTag.push_back(ProtocolTag::ROOM_USER_LIST);
	AllTag.push_back(ProtocolTag::TAG_EXIT);
}

bool ValidateMessage(char* msg)
{
	for (int i = 0; i < AllTag.size(); i++)
	{
		if (_strcmpi(msg, to_string(int(AllTag[i])).c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

void AddTag(char* msg)
{
	int i = 0;
	int msgLength = strlen(msg);
	char* cpy = new char[msgLength + 1];
	memcpy(cpy, msg, (msgLength + 1) * sizeof(char));
	while (cpy[i] != '\0')
	{
		msg[i + 4] = cpy[i];
		i++;
	}
	msg[0] = '1';
	msg[1] = '0';
	msg[2] = '1';
	msg[3] = ' ';
	msg[i + 4] = '\0';
	delete[] cpy;
}