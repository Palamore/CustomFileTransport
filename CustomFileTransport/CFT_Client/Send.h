#pragma once
#include "IncludeDefineNamespace.h"

namespace Send
{
	class Network_Send
	{
		public:

		void SendPacket(std::string serializedPacket);
		void SendLoginRequest(std::string data);
		void SendChatNormal(std::string msg);
		void SendChatWhisper(std::string targetNickname, std::string data);
		void SendRoomListRequest(std::string data);
		void SendExitRequest(std::string data);

		std::string nickname;
		SOCKET clientSocket;
	};
}