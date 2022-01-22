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
#include "UDPFileSend.pb.h"
#include "CommonTools.h"

using namespace std;
using namespace PacketTag;
using namespace UDP;
#define UDP_PORT		8001
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 1000
#define HEADER_SIZE 9
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define UDP_CLIENT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Client.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta_server.txt"
#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"

void RunServer(short nPort);
void RunSendThread();
void RunListenThread();

SOCKET s;
SOCKADDR_IN serverAddr;
SOCKADDR_IN clientAddr;

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
	s;

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		cout << "wrong socket made" << endl;
		return;
	}

	serverAddr;
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

	clientAddr;

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

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	t1.join();
	t2.join();
	delete[] buffer;
	closesocket(s);

	cout << "Done" << endl;
	return;
}


void RunSendThread()
{
	int nRet = 0;
	char* buffer = new char[UDP_PAYLOAD_SIZE];
	int index = 1;
	bool lastFlag = false;
	while (true)
	{
		
	}
}

void RunListenThread()
{
	int nRet = 0;
	char* dataBuffer;
	int nLen = sizeof(SOCKADDR);

	dataBuffer = new char[UDP_PAYLOAD_SIZE];
	char* buffer = new char[UDP_PAYLOAD_SIZE + HEADER_SIZE];
	while (1)
	{
		memset(buffer, 0, (UDP_PAYLOAD_SIZE + HEADER_SIZE) * sizeof(char));
		memset(dataBuffer, 0, (UDP_PAYLOAD_SIZE) * sizeof(char));

		nRet = recvfrom(s, buffer, UDP_PAYLOAD_SIZE + HEADER_SIZE, 0, (LPSOCKADDR)&clientAddr, &nLen);

		string recvData(buffer);

		FileData data;
		if (!data.ParseFromString(recvData))
		{
			cout << "data Parsing Error" << endl;
			closesocket(s);
			return;
		}
		cout << "index : " << data.index() << endl;
		cout << "data : " << data.data() << endl;
		if (nRet < 0)
		{
			cout << "recv error" << endl;
			closesocket(s);
			return;
		}

	}
}