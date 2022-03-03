// √‚√≥ http://cakel.tistory.com
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
#include "Debug.h"

using namespace std;
using namespace PacketTag;
using namespace UDP;
#define SERVER_IP		"127.0.0.1"
#define PUBLIC_SERVER_IP "121.134.137.247"
#define UDP_PORT		8001
#define UDP_RECV_PORT		8002
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 10000
#define ACK_SIZE 1000
#define HEADER_SIZE 5
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
size_t payloadLength;
vector<int> indexContainer;
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

	string serverIP = PUBLIC_SERVER_IP;
	//string serverIP = SERVER_IP;

	

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

	payloadLength = fileSize / UDP_PAYLOAD_SIZE + 1;

	indexContainer.reserve(payloadLength);
	for (int i = 1; i <= payloadLength; i++)
	{
		indexContainer.push_back(i);
	}

	//ofstream openStream;
	//openStream.open("copied.jpg", ios::binary);

	//fileStream.seekg(0, ios::end);

	//char* buffer2;
	////int sz = fileStream.tellg();
	//int sz = 1000;
	//buffer = new char[sz];
	//buffer2 = new char[sz];
	//for (int i = 0; i < 4; i++)
	//{
	//	fileStream.seekg(i * sz, ios::beg);
	//	fileStream.read(buffer, sz);

	//	memcpy(buffer2, buffer, sz);

	//	openStream.write(buffer, sz);
	//}

	//delete[] buffer;
	//delete[] buffer2;

	//sz = 196;
	//buffer = new char[sz];
	//buffer2 = new char[sz];
	//fileStream.seekg(4000, ios::beg);
	//fileStream.read(buffer, sz);

	//memcpy(buffer2, buffer, sz);

	//openStream.write(buffer, sz);

	//cout << "break" << endl;
	//fileStream.close();
	//openStream.close();

	std::thread t1(RunSendThread);
	std::thread t2(RunListenThread);


	t1.join();
	t2.join();
	fileStream.close();
	closesocket(s);

	printf("---------------------Done---------------------");
	
	while (true)
	{

	}
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

	printf("Start Send Thread");

	while (true)
	{
		if (indexOverFlow)
		{
			if (!indexContainer.empty())
			{
				index = indexContainer[0];
			}
		}
		for (int i = 0; i < indexContainer.size(); i++)
		{
			if (indexContainer[i] == index)
			{
				indexExistFlag = true;
				break;
			}
		}
		if (indexContainer.empty())
		{
			printf("End Send Thread\n");
			break;
		}
		if (!indexExistFlag) continue;

		if (index == 3)
		{
			cout << "catch" << endl;
		}
		memset(buffer, 0, UDP_PAYLOAD_SIZE * sizeof(char));

		if (UDP_PAYLOAD_SIZE * index < fileSize)
		{
			fileStream.read(buffer, UDP_PAYLOAD_SIZE);
			/*buffer[UDP_PAYLOAD_SIZE] = '\0';*/
			fileStream.seekg(UDP_PAYLOAD_SIZE * index, std::ios::beg);
			
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

		int payloadSize = UDP_PAYLOAD_SIZE + HEADER_SIZE;
		int lastPayloadSize = fileSize % UDP_PAYLOAD_SIZE + _data.length();
		char* sendBuffer = new char[payloadSize];

		memset(sendBuffer, 0, payloadSize * sizeof(char));
		memcpy(sendBuffer, _data.c_str(), _data.length());


		if (UDP_PAYLOAD_SIZE * index < fileSize)
		{
			memcpy((sendBuffer + HEADER_SIZE), buffer, UDP_PAYLOAD_SIZE);
			nRet = sendto(s, sendBuffer, payloadSize, 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
		}
		else
		{
			memcpy((sendBuffer + HEADER_SIZE), buffer, lastPayloadSize - _data.length());
			nRet = sendto(s, sendBuffer, lastPayloadSize, 0, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
		}


		if (nRet == SOCKET_ERROR)
		{
			printf("send failed\n");
		}
		else
		{
			//printf("Sent index : %d, nRet : %d\n", index, nRet);
			Debug::Log("Sent index : " + to_string(index) + ", nRet : " + to_string(nRet));
		}


		if (indexOverFlow)
		{
			if (!indexContainer.empty())
			{
				index = indexContainer[0];
				//printf("				index overflow, index restart : %d.\n", index);
				Debug::Log("				index overflow, index restart : " + to_string(index));
			}
		}
		else
			index++;
		if (indexContainer.empty())
		{
			printf("End Send Thread\n");
			break;
		}
		indexExistFlag = false;
	}
}

void RunListenThread()
{
	int nRet = 0;

	char* buffer = new char[ACK_SIZE];
	int nLen = sizeof(saClient);
	DataRcvDone done;

	printf("Start Listen Thread");

	while (true)
	{
		memset(buffer, 0, ACK_SIZE * sizeof(char));


		nRet = recvfrom(s, buffer, ACK_SIZE, 0, (LPSOCKADDR)&saClient, &nLen);
		
		if (nRet > 0)
		{
			DataRcvAck ack;
			if (!ack.ParseFromString(buffer))
			{
				printf("ack data parsing failed.\ntry parse DataRcvDone\n");
				if (!done.ParseFromString(buffer))
				{
					printf("done parsing failed.\n");
					break;
				}
				else
				{
					printf("File Sending End.\n");
					break;
				}
			}
			int idx = ack.index();

			
			if (CommonTools::Remove(indexContainer, idx))
			{
				//printf("							Index Ack : %d, nRet : %d\n", idx, nRet);
				Debug::Log("							Index Ack : " + to_string(idx) + ", nRet : " + to_string(nRet));
				if (indexContainer.size() > 5)
					Debug::Log("              Index Removed : " + to_string(idx) + " initial five : " + to_string(indexContainer[0]) + " : " + to_string(indexContainer[1]) + " : " + to_string(indexContainer[2]) + " : " + to_string(indexContainer[3]) + " : " + to_string(indexContainer[4]));
			}
			else
			{
				//printf("Index Ack : %d but Failed to remove\n", idx);
				Debug::Log("Index Ack : " + to_string(idx) + " but Failed to remove");
			}
		}

		if (indexContainer.empty())
		{
			printf("End Listen Thread\n");
			break;
		}
			

	}

}