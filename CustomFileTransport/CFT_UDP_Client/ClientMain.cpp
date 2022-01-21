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
#include "UDPFileSend.pb.h"
#include "CommonTools.h"

using namespace std;
using namespace PacketTag;
using namespace UDP;
#define SERVER_IP		"127.0.0.1"
#define UDP_PORT		8001
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 1000
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define UDP_CLIENT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Client.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta_client.txt"
#define FILE_TO_SEND_PATH "C:\\CustomFileTransport\\CustomFileTransport\\CFT_Client\\"
#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"

void RunClient(const char* szServer, short nPort);

void RunSendThread();
void RunListenThread();


ifstream fileStream;
SOCKET s;
SOCKADDR_IN saServer;
size_t contentsLength;
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

	

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s == INVALID_SOCKET)
	{
		cout << "making socket failed" << endl;
	}

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
	string fileName = metaData[METADATA_FILENAME];
	size_t fileSize = atoi(metaData[METADATA_FILESIZE].c_str());
	contentsLength = atoi(metaData[METADATA_CONTENTSLENGTH].c_str());

	cout << "buffer : " << buffer << endl;
	delete[] buffer;
	cout << "FileName : " << fileName << endl;
	cout << "FileSize : " << fileSize << endl;


	fileStream.open(FILE_TO_SEND_PATH + fileName, ios::binary);
	//fileStream.seekg(0, ios::end);
	//fileLength = fileStream.tellg();
	//fileStream.seekg(0, ios::beg);

	std::thread t1(RunSendThread);
	std::thread t2(RunListenThread);


	t1.join();
	t2.join();
	fileStream.close();
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
		string str = "";
		if (UDP_PAYLOAD_SIZE * index < contentsLength)
		{
			fileStream.read(buffer, UDP_PAYLOAD_SIZE);
			buffer[UDP_PAYLOAD_SIZE] = '\0';
			fileStream.seekg(UDP_PAYLOAD_SIZE * index, std::ios::beg);
			str = string(buffer);
		}
		else
		{
			int targetLength = contentsLength - (UDP_PAYLOAD_SIZE * (index - 1));
			fileStream.read(buffer, targetLength);
			buffer[targetLength] = '\0';
			fileStream.seekg(0, std::ios::beg);
			str = string(buffer);
			str.erase(str.end() - 4, str.end());
			lastFlag = true;
		}

		FileData data;
		data.set_index(index);
		data.set_data(buffer);

		nRet = sendto(s, data.SerializeAsString().c_str(), UDP_PAYLOAD_SIZE, 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
		if (nRet == SOCKET_ERROR)
		{
			cout << "send failed" << endl;
		}
		cout << str;

		if (lastFlag) break;
		index++;
	}
}

void RunListenThread()
{

}