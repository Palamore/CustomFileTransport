#pragma once
#include <vector>
#include <string>
#include "ClientInfo.pb.h"
#include <WinSock2.h>
#include "IOCompletionPort.h"

using namespace std;

namespace Recv
{
	class Network_Recv
	{
	public:

		void Init(vector<ServerPacket::ClientInfo*>* _clientInfoContainer, vector<SOCKET*>* _connectedClients, stSOCKETINFO* _serverSocketInfo);
		void OnRcvLoginRequest(string data);
		void OnRcvChatNormal(string data);
		void OnRcvChatWhisper(string data);
		void OnRcvRoomListRequest(string data);
		void OnRcvExitRequest(string data);

		stSOCKETINFO* socketInfo;
		vector<ServerPacket::ClientInfo*>* clientInfoContainer;
		vector<SOCKET*>* connectedClients;
		stSOCKETINFO* serverSocketInfo;

	};
}
