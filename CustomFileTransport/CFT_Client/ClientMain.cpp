
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
#define INPUT_COMMAND_INDEX 0
#define INPUT_COMMAND_TYPE_INDEX 1
#define INPUT_TARGET_NICKNAME_INDEX 1
#define INPUT_MESSAGE_INDEX 2

struct stSOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

string nickname;
SOCKET clientSocket;

void Init();
void RunListenThread();
void RunSendThread();
void SendPacket(string serializedPacket);
void SendLoginRequest(string data);
void SendChatNormal(string msg);
void SendChatWhisper(string targetNickname, string data);
void SendRoomListRequest(string data);
void SendExitRequest(string data);
vector<string> Split(string targetStr, char splitter);


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
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	std::cout << "Connection success..." << std::endl;
	while (true) {


	}

	t1.join();
	t2.join();
	closesocket(clientSocket);
	std::cout << "Client has been terminated..." << std::endl;

	return 0;
}

void RunListenThread()
{
	char	sz_socketbuf_[MAX_BUFFER];
	while (1)
	{
		int nRecvLen = recv(clientSocket, sz_socketbuf_, 1024, 0);
		if (nRecvLen == 0) {
			std::cout << "Server connection has been closed" << std::endl;
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

void RunSendThread()
{
	char	szOutMsg[MAX_BUFFER];
	string outMsg;

	std::cout << "Nickname : ";
	std::cin >> nickname;

	SendLoginRequest("");

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
				SendChatWhisper(splitted[INPUT_TARGET_NICKNAME_INDEX], msg);
				break;
			case 'l':
				SendRoomListRequest(splitted[INPUT_MESSAGE_INDEX]);
				break;
			case 'e':
				SendExitRequest(splitted[INPUT_MESSAGE_INDEX]);
				exit(0);
				break;
			default:
				break;
			}
		}
		SendChatNormal(szOutMsg);
	}
}


void Init()
{

}

void SendPacket(string serializedPacket)
{
	int sendResult = send(clientSocket, serializedPacket.c_str(), strlen(serializedPacket.c_str()), 0);
	if (sendResult == -1) {
		std::cout << "Error : " << WSAGetLastError() << std::endl;
		return;
	}
}

void SendLoginRequest(string data)
{
	LoginRequest loginData;
	loginData.set_nickname(nickname);
	loginData.set_data(data);

	PacketMsg packet;
	packet.set_nickname(nickname);
	packet.set_type(PacketType::LOGIN_REQUEST);
	packet.set_data(loginData.SerializeAsString());

	SendPacket(packet.SerializeAsString());

	cout << "[LOGIN_REQUEST]" << endl;
}

void SendChatNormal(string msg)
{
	ChatNormal chatData;
	chatData.set_data(msg);

	PacketMsg packet;
	packet.set_nickname(nickname);
	packet.set_type(PacketType::CHAT_NORMAL);
	packet.set_data(chatData.SerializeAsString());

	SendPacket(packet.SerializeAsString());

	std::cout << "[CHAT_NORMAL]" << std::endl <<
		msg << std::endl;
}

void SendChatWhisper(string targetNickname, string data)
{
	ChatWhisper chatData;
	chatData.set_targetnickname(targetNickname);
	chatData.set_data(data);

	PacketMsg packet;
	packet.set_nickname(nickname);
	packet.set_type(PacketType::CHAT_WHISPER);
	packet.set_data(chatData.SerializeAsString());

	SendPacket(packet.SerializeAsString());

	std::cout << "[CHAT_WHISPER]" << std::endl <<
		"to " << targetNickname << " : " << data << std::endl;
}

void SendRoomListRequest(string data)
{
	UserListRequest roomList;
	roomList.set_data(data);

	PacketMsg packet;
	packet.set_nickname(nickname);
	packet.set_type(PacketType::USER_LIST_REQUEST);
	packet.set_data(roomList.SerializeAsString());

	SendPacket(packet.SerializeAsString());

	cout << "[ROOM_USER_LIST]" << endl;
}

void SendExitRequest(string data)
{
	ExitRequest exitReq;
	exitReq.set_data(data);

	PacketMsg packet;
	packet.set_nickname(nickname);
	packet.set_type(PacketType::EXIT_REQUEST);
	packet.set_data(exitReq.SerializeAsString());

	SendPacket(packet.SerializeAsString());

	cout << "[EXIT_REQUEST]" << endl;
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