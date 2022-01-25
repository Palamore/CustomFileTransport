// 출처 http://cakel.tistory.com
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
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
#define UDP_RECV_PORT		8002
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 1000
#define HEADER_SIZE 9
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
FILE* fp;
SOCKET s;
SOCKET s_recv;
SOCKADDR_IN saServer;
SOCKADDR_IN saClient;
size_t contentsLength;
size_t fileSize;

vector<int> indexContainer;
list<int> idxcont;
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
	indexContainer.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		indexContainer.push_back(i);
	}
	

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

	s_recv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s_recv == INVALID_SOCKET)
	{
		cout << "making recv socket failed" << endl;
	}


	saServer.sin_family = AF_INET;
	saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	saServer.sin_port = htons(nPort);


	int nRet = 0;

	// Read MetaFile
	ifstream metaFile(METAFILE_PATH, ios::binary);
	int fileLength;
	char* buffer;
	void* vuffer = NULL;
	metaFile.seekg(0, ios::end);
	fileLength = metaFile.tellg();
	metaFile.seekg(0, ios::beg);
	buffer = new char[fileLength];
	metaFile.read(buffer, fileLength);
	metaFile.close();

	map<string, string> metaData = CommonTools::ParseMetaString(buffer);
	string fileName = metaData[METADATA_FILENAME];
	fileSize = atoi(metaData[METADATA_FILESIZE].c_str());
	contentsLength = atoi(metaData[METADATA_CONTENTSLENGTH].c_str());

	cout << "buffer : " << buffer << endl;
	delete[] buffer;
	cout << "FileName : " << fileName << endl;
	cout << "FileSize : " << fileSize << endl;

	fileStream.open(FILE_TO_SEND_PATH + fileName, ios::binary);

	//TODO :: fileStream으로 Binary 파일 읽을시 fileLength만큼 읽고 그 다음 메모리 읽어내기.
	/*ofstream openStream;
	openStream.open("copied.png", ios::binary);

	fileStream.seekg(0, ios::end);

	int sz = fileStream.tellg();
	buffer = new char[sz];
	fileStream.seekg(0, ios::beg);

	fileStream.read(buffer, sz);
	
	openStream.write(buffer, sz);
	cout << "break" << endl;
	fileStream.close();
	openStream.close();*/


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
	void* vuffer;
	int index = 1;
	int lastIndex = -1;
	bool lastFlag = false;
	bool indexOverFlow = false;
	bool indexExistFlag = false;
	while (true)
	{
		string str = "";

		for (int i = 0; i < indexContainer.size(); i++)
		{
			if (indexContainer[i] == index)
			{
				indexExistFlag = true;
				break;
			}
		}
		if (indexContainer.size() + lastIndex == 100)
		{
			break;
		}
		if (!indexExistFlag) continue;

		if (UDP_PAYLOAD_SIZE * index < fileSize)
		{
			fileStream.read(buffer, UDP_PAYLOAD_SIZE);
			/*buffer[UDP_PAYLOAD_SIZE] = '\0';*/
			fileStream.seekg(UDP_PAYLOAD_SIZE * index, std::ios::beg);
			str = string(buffer);
			
		}
		else
		{
			int targetLength = fileSize - (UDP_PAYLOAD_SIZE * (index - 1));
			fileStream.read(buffer, targetLength);
			/*buffer[targetLength] = '\0';*/
			fileStream.seekg(0, std::ios::beg);
			/*str = string(buffer);
			str.erase(str.end() - 4, str.end());*/
			lastIndex = index;
			indexOverFlow = true;
		}
		

		FileData data;
		data.set_index(index);
		
		string _data = data.SerializeAsString();

		int payloadSize = UDP_PAYLOAD_SIZE + _data.length();
		int lastPayloadSize = fileSize % UDP_PAYLOAD_SIZE + _data.length();
		char* sendBuffer = new char[payloadSize];


		memcpy(sendBuffer, _data.c_str(), _data.length());
		

		if (UDP_PAYLOAD_SIZE * index < fileSize)
		{
			memcpy((sendBuffer + _data.length()), buffer, UDP_PAYLOAD_SIZE);
			nRet = sendto(s, sendBuffer, payloadSize, 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
		}
		else
		{
			memcpy((sendBuffer + _data.length()), buffer, lastPayloadSize - _data.length());
			nRet = sendto(s, sendBuffer, lastPayloadSize, 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
		}

		if (nRet == SOCKET_ERROR)
		{
			cout << "send failed" << endl;
		}
		cout << strlen(_data.c_str()) << endl;

		cout << str;

		if (indexContainer.size() + lastIndex == 100)
		{
			break;
		}
		if (indexOverFlow)
			index = 1;
		else
			index++;
		indexExistFlag = false;
	}
}

void RunListenThread()
{
	int nRet = 0;
	char* buffer = new char[6];
	int nLen = sizeof(saClient);

	while (true)
	{
		memset(buffer, 0, 6 * sizeof(char));

		nRet = recvfrom(s, buffer, 6, 0, (LPSOCKADDR)&saClient, &nLen);
		
		if (nRet > 0)
		{
			DataRcvAck ack;
			if (!ack.ParseFromString(buffer))
			{
				cout << "ack data parsing error" << endl;
				break;
			}
			int idx = ack.index();

			for (int i = 0; i < indexContainer.size(); i++)
			{
				if (indexContainer[i] == idx)
				{
					indexContainer.erase(indexContainer.begin() + i);
					break;
				}
			}
			cout << "Index Ack : " + idx << endl;
		}

	}

}