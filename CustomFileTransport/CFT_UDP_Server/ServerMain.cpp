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
#include "PacketTag.pb.h"
#include "ClientInfo.pb.h"
#include "UDPFileSend.pb.h"
#include "CommonTools.h"

using namespace std;
using namespace PacketTag;
using namespace UDP;

#define SERVER_IP		"127.0.0.1"
#define CLIENT_IP		"127.0.0.1"
#define UDP_PORT		8001
#define UDP_RECV_PORT		8002
#define	MAX_BUFFER		1024
#define UDP_PAYLOAD_SIZE 1000
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

vector<int> indexContainer;

class RecvData {
	public:
	FileData indexData;
	char* data;

	RecvData()
	{
		data = new char[UDP_PAYLOAD_SIZE];
	}

	~RecvData()
	{
		delete[] data;
	}

	int GetIndex()
	{
		return indexData.index();
	}
	char* GetData()
	{
		return data;
	}

	bool operator==(RecvData &rhs)
	{
		if (indexData.index() == rhs.indexData.index()) 
		{
			//if (strcmp(data, rhs.data))  일단 인덱스만 검증
				return true;
		}
		return false;
	}
};

vector<RecvData*> dataCont;

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

	//cout << "buffer : " << buffer << endl;
	//cout << "FileName : " << fileData.filename() << endl;
	//cout << "FileSize : " << fileData.filesize() << endl;

	map<string, string> metaData = CommonTools::ParseMetaString(buffer);

	fileName		= metaData[METADATA_FILENAME];
	fileSize		= atoi(metaData[METADATA_FILESIZE].c_str());
	contentsLength  = atoi(metaData[METADATA_CONTENTSLENGTH].c_str());
	payloadCount = (fileSize / UDP_PAYLOAD_SIZE) + 1;
	lastPayloadSize = fileSize % UDP_PAYLOAD_SIZE;

	indexContainer.reserve(payloadCount);
	dataCont.reserve(payloadCount);

	for (int i = 1; i <= payloadCount; i++)
	{
		indexContainer.push_back(i);
	}

	std::thread t1(RunListenThread);
	std::thread t2(RunSendThread);

	t1.join();
	t2.join();
	delete[] buffer;
	closesocket(s);

	printf("---------------------Done---------------------");
	return;
}


void RunSendThread()
{
	int nRet = 0;
	char* buffer = new char[UDP_PAYLOAD_SIZE];
	int curIndex = 1;
	bool lastFlag = false;
	
	ofstream targetFile(fileName, ios::binary);

	vector<int> payloadIndexCont;
	payloadIndexCont.reserve(payloadCount);
	for (int i = 1; i <= payloadCount; i++)
	{
		payloadIndexCont.push_back(i);
	}

	printf("Start Send Thread");

	while (true)
	{
		for (int i = 0 ; i < dataCont.size(); i++)
		{
			int index = dataCont[i]->GetIndex();
			memcpy(buffer, dataCont[i]->data, UDP_PAYLOAD_SIZE);

			if (index == curIndex)
			{
				printf("                                  Try Remove index : %d\n" , curIndex);
				if (curIndex == payloadCount)
				{
					char* lastPayload = new char[lastPayloadSize];
					memcpy(lastPayload, buffer, lastPayloadSize);
					targetFile.write(lastPayload, lastPayloadSize);

					printf("curIndex : %d \n", curIndex);
					delete[] lastPayload;
					targetFile.close();
					delete[] buffer;
					dataCont.clear();
					payloadIndexCont.clear();
					lastFlag = true;
				}

				DataRcvAck ack;
				ack.set_index(index);
				string sendData = ack.SerializeAsString();

				if (sendData.length() > ACK_SIZE)
				{
					printf("Catch");
				}

				nRet = sendto(s, ack.SerializeAsString().c_str(), ACK_SIZE, 0, (LPSOCKADDR)&clientAddr, sizeof(struct sockaddr));
				if (nRet == SOCKET_ERROR)
				{
					printf("send failed Index : %d\n", curIndex);
				}
				else
				{
					printf("Index Sent : %d, nRet : %d \n", curIndex, nRet);
					if (!lastFlag)
					{
						targetFile.write(buffer, UDP_PAYLOAD_SIZE);
						
						CommonTools::Remove(payloadIndexCont, index);
						
						printf("                                  Removed Target Index : %d\n",  dataCont[i]->indexData.index());
						dataCont.erase(dataCont.begin() + i);
						if (dataCont.size() > i)
							printf("                                  After Removed Target Index : %d\n", dataCont[i]->indexData.index());
					}
					curIndex++;
				}

				this_thread::sleep_for(chrono::milliseconds(1)); 


				if (lastFlag)
				{
					break;
				}

			}
		}

		if (payloadIndexCont.empty() && dataCont.empty())
		{
			printf("End Send Thread\n");
			break;
		}

	}
}

void RunListenThread()
{
	int nRet = 0;
	char* dataBuffer;
	int nLen = sizeof(SOCKADDR);
	dataCont.reserve(payloadCount);

	dataBuffer = new char[UDP_PAYLOAD_SIZE];
	char* buffer = new char[UDP_PAYLOAD_SIZE + HEADER_SIZE];

	printf("Start Listen Thread");
	while (true)
	{
		memset(buffer, 0, (UDP_PAYLOAD_SIZE + HEADER_SIZE) * sizeof(char));
		memset(dataBuffer, 0, (UDP_PAYLOAD_SIZE) * sizeof(char));
		char* header = new char[HEADER_SIZE];
		char* binaryData = new char[UDP_PAYLOAD_SIZE];
		string headerStr;
		FileData data;
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
				return;
			}
			if (data.index() == 0)
			{
				delete[] header;
				delete[] binaryData;
				continue;
			}
			printf("recv : %d, nRet : %d\n", data.index(), nRet);
		}
		else
		{
			printf("recv Failed\n");
			delete[] header;
			delete[] binaryData;
			continue;
		}

		RecvData *recvData = new RecvData();
		recvData->indexData = data;
		memcpy(recvData->data, binaryData, UDP_PAYLOAD_SIZE);
		dataCont.push_back(recvData);
		CommonTools::Remove(indexContainer, data.index());



		delete[] header;
		delete[] binaryData;
		if (indexContainer.empty())
		{
			printf("End Listen Thread\n");
			break;
		}
	}

	delete[] dataBuffer;
	delete[] buffer;
}