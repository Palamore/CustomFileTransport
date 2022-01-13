// √‚√≥ http://cakel.tistory.com
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <direct.h>
#include <io.h>
#include <string>

using namespace std;
#define SERVER_IP		"127.0.0.1"
#define UDP_PORT		8001
#define	MAX_BUFFER		1024

void RunClient(const char* szServer, short nPort);


int main()
{
	WORD versionWord = MAKEWORD(1, 1);
	WSADATA wsaData;
	int nRet;
	short nPort;

	nPort = UDP_PORT;

	nRet = WSAStartup(versionWord, &wsaData);
	if (wsaData.wVersion != versionWord)
	{
		cout << "wrong version" << endl;
		return -1;
	}

	string serverIP = SERVER_IP;

	RunClient(serverIP.c_str(), nPort);


	return 0;
}

void RunClient(const char* szServer, short nPort)
{
	LPHOSTENT lpHostEntry;

	lpHostEntry = gethostbyname(szServer);

	if (lpHostEntry == NULL)
	{
		cout << "get host name failed" << endl;
		return;
	}

	SOCKET s;

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s == INVALID_SOCKET)
	{
		cout << "making socket failed" << endl;
	}

	SOCKADDR_IN saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	saServer.sin_port = htons(nPort);

	char szBuf[MAX_BUFFER];

	int nRet;

	strcpy(szBuf, "Test Message. senttt");

	nRet = sendto(s, szBuf, strlen(szBuf), 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		cout << "send failed" << endl;
		closesocket(s);
		return;
	}

	memset(szBuf, 0, sizeof(szBuf));

	closesocket(s);
	return;
}