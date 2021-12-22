#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 4000
#define PACKET_SIZE 1024
#define SERVER_IP "127.0.0.1"

int LogError(string str)
{
	cout << "ERROR : " + str + "\n" << endl;
	return -1;
}

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) return LogError(string("WSAStartup Failed"));

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (hSocket == NULL)
		return LogError(string("hSocket Socket is Null"));

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	char cMsg[] = "Client Send";
	send(hSocket, cMsg, strlen(cMsg), 0);

	char cBuffer[PACKET_SIZE] = {};
	recv(hSocket, cBuffer, PACKET_SIZE, 0);

	cout << "Recv Msg : " << cBuffer << endl;

	closesocket(hSocket);

	WSACleanup();
	return 0;
}
