// 출처 http://cakel.tistory.com
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <direct.h>
#include <io.h>
#include <vector>
#include <map>
#include <mutex>
#include <ctime>
#include "PacketTag.pb.h"
#include "ClientInfo.pb.h"
#include "UDPFileSend.pb.h"
#include "CommonTools.h"
#include "Debug.h"

using namespace std;
using namespace PacketTag;
using namespace UDP;

#define SERVER_IP		"127.0.0.1"
#define CLIENT_IP		"127.0.0.1"
#define UDP_PORT		8001
#define UDP_RECV_PORT		8002
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 10000
#define ACK_SIZE 1000
#define HEADER_SIZE 5
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define UDP_CLIENT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Client.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta_server.txt"
#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"

void RunServer(short nPort);
void RunFileWriteThread();
void RunSendThread();
void RunListenThread();

SOCKET s;
SOCKET s_send;
SOCKADDR_IN serverAddr;
SOCKADDR_IN clientAddr;

string fileName;
int fileSize;
int contentsLength;
int payloadCount;
int lastPayloadSize;
bool doneFlag = false;

//mutex m;

class RecvData {
	public:
	char* data;
	bool RecvFlag;
	bool SendFlag;
	bool WriteFlag;

	RecvData()
		: data(new char[UDP_PAYLOAD_SIZE])
		, RecvFlag(false)
		, SendFlag(false)
		, WriteFlag(false)
	{
	}
	~RecvData()
	{
		delete[] data;
	}
};

map<int, RecvData*> dataDic;

//vector<RecvData*> dataCont;

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
	LPHOSTENT lpHostEntry;

	lpHostEntry = gethostbyname(CLIENT_IP);

	if (lpHostEntry == NULL)
	{
		cout << "get host name failed" << endl;
		return;
	}

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		cout << "wrong socket made" << endl;
		return;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(nPort);

	//clientAddr.sin_family = AF_INET;
	//clientAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	//clientAddr.sin_port = htons(UDP_RECV_PORT);

	s_send = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s_send == INVALID_SOCKET)
	{
		cout << "wrong socket made" << endl;
		return;
	}

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

	fileName		= metaData[METADATA_FILENAME];
	fileSize		= atoi(metaData[METADATA_FILESIZE].c_str());
	contentsLength  = atoi(metaData[METADATA_CONTENTSLENGTH].c_str());
	payloadCount = (fileSize / UDP_PAYLOAD_SIZE) + 1;
	lastPayloadSize = fileSize % UDP_PAYLOAD_SIZE;


	for (int i = 1; i <= payloadCount; i++)
	{
		RecvData* d = new RecvData();
		dataDic.insert({ i, d });
	}
	clock_t start = clock();

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	/*std::thread t3(RunListenThread);
	std::thread t4(RunListenThread);*/

	t1.join();
	t2.join();
	std::thread t3(RunFileWriteThread);

	t3.join();
	delete[] buffer;
	closesocket(s);

	clock_t end = clock();

	cout << "whole time : " << difftime(end, start) / 1000.0 << endl;

	printf("---------------------Done---------------------");

	while (true)
	{

	}

	return;
}

void RunFileWriteThread()
{
	int curIndex = 1;
	bool lastFlag = false;

	vector<int> writeIndexCont;
	writeIndexCont.reserve(payloadCount);
	for (int i = 1; i <= payloadCount; i++)
	{
		writeIndexCont.push_back(i);
	}
	ofstream targetFile(fileName, ios::binary);

	printf("Start Write Thread\n");

	while (true)
	{
		map<int, RecvData*>::iterator iter = dataDic.find(curIndex);

		if (iter->second->RecvFlag == false)
		{
			continue;
		}
		
		if (curIndex == payloadCount)
		{
			char* lastPayload = new char[lastPayloadSize];
			memcpy(lastPayload, iter->second->data, lastPayloadSize);
			targetFile.write(lastPayload, lastPayloadSize);
			printf("										Write Index : %d.\n", curIndex);

			delete[] lastPayload;
			targetFile.close();
			writeIndexCont.clear();
			printf("End Write Thread\n");
			break;
		}

		targetFile.write(iter->second->data, UDP_PAYLOAD_SIZE);
		CommonTools::Remove(writeIndexCont, curIndex);
		printf("										Write Index : %d.\n", curIndex);

		curIndex++;
	}
}

void RunSendThread()
{
	int nRet = 0;
	char* buffer = new char[UDP_PAYLOAD_SIZE];
	int curIndex = 1;
	bool lastFlag = false;
	
	ofstream targetFile(fileName, ios::binary);

	vector<int> sendIndexCont;
	sendIndexCont.reserve(payloadCount);
	for (int i = 1; i <= payloadCount; i++)
	{
		sendIndexCont.push_back(i);
	}

	printf("Start Send Thread\n");
	
	while (true)
	{
		for (int i = 0 ; i < sendIndexCont.size(); i++)
		{
			int curIndex = sendIndexCont[i];
			map<int, RecvData*>::iterator iter = dataDic.find(curIndex);
			if (iter->second->RecvFlag == false)
			{
				continue;
			}
			
			DataRcvAck ack;
			ack.set_index(curIndex);
			string sendData = ack.SerializeAsString();

			nRet = sendto(s, sendData.c_str(), ACK_SIZE, 0, (LPSOCKADDR)&clientAddr, sizeof(struct sockaddr));
			if (nRet == SOCKET_ERROR)
			{
				printf("Send Failed index : %d\n", curIndex);
			}
			else
			{

				iter->second->SendFlag = true;
				CommonTools::Remove(sendIndexCont, curIndex);
				//printf("					Sent Index : %d.\n", curIndex);
				Debug::Log("					Sent Index : " + to_string(curIndex));
				//if (iter->second->WriteFlag == true) //Send, Write 모두 끝난 경우 날림
				//{
				//	dataDic.erase(curIndex);
				//}
			}
			
		}
		if (sendIndexCont.empty())
		{
			printf("End Send Thread.\n");
			break;
		}
	}
}

void RunListenThread()
{
	int nRet = 0;
	char* dataBuffer;
	int nLen = sizeof(SOCKADDR);
	
	vector<int> recvIndexCont;

	recvIndexCont.reserve(payloadCount);
	for (int i = 1; i <= payloadCount; i++)
	{
		recvIndexCont.push_back(i);
	}
	dataBuffer = new char[UDP_PAYLOAD_SIZE];
	char* buffer = new char[UDP_PAYLOAD_SIZE + HEADER_SIZE];

	printf("Start Listen Thread\n");
	while (true)
	{
		memset(buffer, 0, (UDP_PAYLOAD_SIZE + HEADER_SIZE) * sizeof(char));
		memset(dataBuffer, 0, (UDP_PAYLOAD_SIZE) * sizeof(char));
		char* header = new char[HEADER_SIZE];
		char* binaryData = new char[UDP_PAYLOAD_SIZE];
		string headerStr;
		FileData data;
		//m.lock();
		nRet = recvfrom(s, buffer, UDP_PAYLOAD_SIZE + HEADER_SIZE, 0, (LPSOCKADDR)&clientAddr, &nLen);
		if (nRet > 0)
		{
			memcpy(header, buffer, HEADER_SIZE);
			memcpy(binaryData, buffer + HEADER_SIZE, UDP_PAYLOAD_SIZE);
			headerStr = header;
			if (!data.ParseFromString(headerStr))
			{
				printf("data Parsing Error");
				closesocket(s);
				delete[] dataBuffer;
				delete[] buffer;
				//m.unlock();
				return;
			}
			if (data.index() == 0)
			{
				delete[] header;
				delete[] binaryData;
				//m.unlock();
				continue;
			}
			//printf("recv index : %d, nRet : %d\n", data.index(), nRet);
			Debug::Log("recv index : " + to_string(data.index()) + ", nRet : " + to_string(nRet));
		}
		else
		{
			printf("recv Failed\n");
			delete[] header;
			delete[] binaryData;
			//m.unlock();
			continue;
		}

		map<int, RecvData*>::iterator iter = dataDic.find(data.index());
		if (CommonTools::Find(recvIndexCont, data.index()))
		{
			memcpy(iter->second->data, binaryData, UDP_PAYLOAD_SIZE);
			iter->second->RecvFlag = true;
			CommonTools::Remove(recvIndexCont, data.index());
		}
		else //못 찾는 경우 해당 Index의 Ack 데이터그램을 클라이언트에서 못 받은 경우일 수 있으므로 해당 index의 Ack 데이터그램 재전송.
		{    
			if (iter->second->SendFlag == true)
			{
				DataRcvAck ack;
				ack.set_index(data.index());
				string sendData = ack.SerializeAsString();

				nRet = sendto(s, sendData.c_str(), ACK_SIZE, 0, (LPSOCKADDR)&clientAddr, sizeof(struct sockaddr));
			}
		}

		delete[] header;
		delete[] binaryData;
		if (recvIndexCont.empty())
		{
			printf("End Listen Thread\n");
			//m.unlock();
			break;
		}
		//m.unlock();
	}

	delete[] dataBuffer;
	delete[] buffer;
}