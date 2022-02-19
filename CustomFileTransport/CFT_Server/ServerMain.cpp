#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <string>
#include "IOCompletionPort.h"
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 8000
#define PACKET_SIZE 1024
vector<ClientInfo*>* clientInfoContainer;

int main()
{
	//clientInfoContainer = new vector<ClientInfo*>();
	//ClientInfo* cInfo = new ClientInfo();
	//cInfo->set_socket(108);
	//cInfo->set_nickname("108");
	//clientInfoContainer->push_back(cInfo);

	//cInfo = new ClientInfo();
	//cInfo->set_socket(110);
	//cInfo->set_nickname("110");
	//clientInfoContainer->push_back(cInfo);

	//clientInfoContainer->erase(clientInfoContainer->begin() + 1);


	IOCompletionPort iocp_server;
	if (iocp_server.Initialize())
	{
		iocp_server.StartServer();
	}

	return 0;
}