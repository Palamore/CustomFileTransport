#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <string>
#include "IOCompletionPort.h"
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 4000
#define PACKET_SIZE 1024


int main()
{
	IOCompletionPort iocp_server;
	if (iocp_server.Initialize())
	{
		iocp_server.StartServer();
	}

	return 0;
}