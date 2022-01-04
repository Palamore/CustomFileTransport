#include "Recv.h"
#include "Debug.h"

namespace Recv
{
	void Network_Recv::Init(vector<ServerPacket::ClientInfo*>* _clientInfoContainer, vector<SOCKET*>* _connectedClients, stSOCKETINFO* _serverSocketInfo)
	{
		clientInfoContainer = _clientInfoContainer;
		connectedClients = _connectedClients;
		serverSocketInfo = _serverSocketInfo;
	}

	void Network_Recv::OnRcvLoginRequest(string data)
	{
		PacketTag::LoginRequest loginData;
		if (!loginData.ParseFromString(data))
		{
			Debug::LogError("ChatData Parsing Failed");
			return;
		}

		for (int i = 0; i < clientInfoContainer->size(); i++)
		{
			if (serverSocketInfo->socket == clientInfoContainer->at(i)->socket())
			{
				clientInfoContainer->at(i)->set_nickname(loginData.nickname());
				return;
			}
		}
	}

	void Network_Recv::OnRcvChatNormal(string data)
	{
		PacketTag::ChatNormal chatData;
		if (!chatData.ParseFromString(data))
		{
			Debug::LogError("ChatData Parsing Failed");
			return;
		}
		int		nResult = 0;
		DWORD	dwFlags = 0;
		DWORD	sendBytes = 0;

		socketInfo->dataBuf.buf = (CHAR*)(chatData.data().c_str());
		socketInfo->dataBuf.len = strlen(chatData.data().c_str());
		for (int i = 0; i < connectedClients->size(); i++)
		{
			nResult = WSASend(
				*(connectedClients->at(i)),
				&(socketInfo->dataBuf),
				1,
				&sendBytes,
				dwFlags,
				null,
				null
			);
			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
			}
			Debug::Log("Msg Sent : " + string(socketInfo->dataBuf.buf) + "\n");
		}
	}

	void Network_Recv::OnRcvChatWhisper(string data)
	{
		PacketTag::ChatWhisper chatData;
		if (!chatData.ParseFromString(data))
		{
			Debug::LogError("ChatData Parsing Failed");
			return;
		}

		int		nResult = 0;
		DWORD	dwFlags = 0;
		DWORD	sendBytes = 0;
		string targetNickname = "";

		for (int i = 0; i < clientInfoContainer->size(); i++)
		{
			if (clientInfoContainer->at(i)->nickname() == chatData.targetnickname())
			{
				targetNickname = chatData.targetnickname();
			}
		}

		if (targetNickname == "")
		{
			string FailMsg("No one has that Nickname.");
			socketInfo->dataBuf.buf = (CHAR*)(FailMsg.c_str());
			socketInfo->dataBuf.len = FailMsg.length();
			for (int i = 0; i < connectedClients->size(); i++)
			{
				nResult = WSASend(
					*(connectedClients->at(i)),
					&(socketInfo->dataBuf),
					1,
					&sendBytes,
					dwFlags,
					null,
					null
				);
				if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
				{
					Debug::LogError("WSASend Failed : " + to_string(WSAGetLastError()));
				}
				Debug::Log("Msg Sent : " + string(socketInfo->dataBuf.buf) + "\n");
			}
		}
	}

	void Network_Recv::OnRcvRoomListRequest(string data)
	{

	}

	void Network_Recv::OnRcvExitRequest(string data)
	{

	}

}