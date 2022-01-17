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
#include <shellapi.h>
#include "PacketTag.pb.h"
#include "ClientInfo.pb.h"
#include "CommonTools.h"

using namespace std;
#define SERVER_IP		"127.0.0.1"
#define UDP_PORT		8001
#define	MAX_BUFFER		1024
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta.txt"



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


	int nRet;

	// Read MetaFile
	ifstream metaFile(METAFILE_PATH, ios::binary);
	int fileLength;
	char* buffer;
	metaFile.seekg(0, ios::end);
	fileLength = metaFile.tellg();
	metaFile.seekg(0, ios::beg);
	buffer = new char[fileLength];
	metaFile.read(buffer, fileLength);
	metaFile.close();

	map<string, string> metaData = CommonTools::ParseMetaString(buffer);
	string fileName = metaData["Filename"];
	size_t fileSize = atoi(metaData["Filesize"].c_str());

	cout << "buffer : " << buffer << endl;
	delete[] buffer;
	cout << "FileName : " << fileName << endl;
	cout << "FileSize : " << fileSize << endl;


	ifstream fileStream(fileName, ios::binary);
	fileStream.seekg(0, ios::end);
	fileLength = fileStream.tellg();
	fileStream.seekg(0, ios::beg);
	buffer = new char[fileLength];
	fileStream.read(buffer, fileLength);
	fileStream.close();

	nRet = sendto(s, buffer, strlen(buffer), 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
	if (nRet == SOCKET_ERROR)
	{
		cout << "send failed" << endl;
		closesocket(s);
		return;
	}

	cout << buffer << endl;
	while (1)
	{

	}

	delete[] buffer;

	closesocket(s);
	return;
}