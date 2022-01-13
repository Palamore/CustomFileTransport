// √‚√≥ http://cakel.tistory.com
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <direct.h>
#include <io.h>

using namespace std;
#define UDP_PORT		8001
#define	MAX_BUFFER		1024

void RunServer(short nPort);

int main(int _fileSize)
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
	
	RunServer(nPort);


	return 0;
}


void RunServer(short nPort)
{
	SOCKET s;

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		cout << "wrong socket made" << endl;
		return;
	}

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(nPort);

	int nRet;

	nRet = bind(s, (LPSOCKADDR)&serverAddr, sizeof(struct sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		cout << "bind failed" << endl;
		closesocket(s);
		return;
	}

	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[MAX_BUFFER];

	nRet = gethostname(szBuf, sizeof(szBuf));
	if (nRet == SOCKET_ERROR)
	{
		cout << "wrong host name return" << endl;
		closesocket(s);
		return;
	}

	SOCKADDR_IN clientAddr;

	while (1)
	{
		memset(szBuf, 0, sizeof(szBuf));

		nRet = recvfrom(s, szBuf, sizeof(szBuf), 0, (LPSOCKADDR)&clientAddr, &nLen);

		if (nRet < 0)
		{
			cout << "recv error" << endl;
			closesocket(s);
			return;
		}

		cout << "recv : " << szBuf << endl;

	}


}
