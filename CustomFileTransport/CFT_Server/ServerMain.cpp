#include "IOCompletionPort.h"

#pragma comment(lib, "ws2_32.lib")
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