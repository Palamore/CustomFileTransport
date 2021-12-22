#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <string>
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 4000
#define PACKET_SIZE 1024

int LogError(string str)
{
	cout << "ERROR : " + str + "\n" << endl;
	return -1;
}

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) return LogError(string("WSAStartup Failed"));

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hListen == NULL)
		return LogError(string("Listener Socket is Null"));

	SOCKADDR_IN listenAddr = {};
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(PORT);
	listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind((hListen), (SOCKADDR*)&listenAddr, sizeof(listenAddr));
	listen(hListen, SOMAXCONN);

	SOCKADDR_IN clientAddr = {};
	int clientSize = sizeof(clientAddr);
	SOCKET client = accept(hListen, (SOCKADDR*)&clientAddr, &clientSize);
	cout << "Client Accepted" << endl;


	char cBuffer[PACKET_SIZE] = {};
	recv(client, cBuffer, PACKET_SIZE, 0);
	cout << "Message Recieved" << endl;

	char cMsg[] = "Server Send";
	send(client, cMsg, strlen(cMsg), 0);
	cout << "Message Sent" << endl;


	closesocket(client);
	closesocket(hListen);

	WSACleanup();

	return 0;
}