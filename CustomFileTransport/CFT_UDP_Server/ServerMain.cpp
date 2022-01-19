// √‚√≥ http://cakel.tistory.com
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <direct.h>
#include <io.h>
#include "PacketTag.pb.h"
#include "ClientInfo.pb.h"
#include "CommonTools.h"

using namespace std;
#define UDP_PORT		8001
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 1000
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define UDP_CLIENT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Client.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta_server.txt"
#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"

void RunServer(short nPort);

int main(const char* arg)
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

	//cout << "buffer : " << buffer << endl;
	//cout << "FileName : " << fileData.filename() << endl;
	//cout << "FileSize : " << fileData.filesize() << endl;

	map<string, string> metaData = CommonTools::ParseMetaString(buffer);

	string fileName = metaData[METADATA_FILENAME];
	int fileSize = atoi(metaData[METADATA_FILESIZE].c_str());
	int contentsLength = atoi(metaData[METADATA_CONTENTSLENGTH].c_str());


	delete[] buffer;
	buffer = new char[UDP_PAYLOAD_SIZE];
	while (1)
	{
		memset(buffer, 0, fileLength);

		nRet = recvfrom(s, buffer, UDP_PAYLOAD_SIZE, 0, (LPSOCKADDR)&clientAddr, &nLen);

		if (nRet < 0)
		{
			cout << "recv error" << endl;
			closesocket(s);
			return;
		}

		cout << "recv : " << buffer << endl;

	}


}
