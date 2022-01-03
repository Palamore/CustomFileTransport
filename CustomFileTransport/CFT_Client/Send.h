#pragma once
#include "IncludeDefineNamespace.h"

namespace Send
{
	class Network_Send
	{
		public:


			void SendPacket(string serializedPacket);
			void SendLoginRequest(string data);
		void SendChatNormal(string msg);
		void SendChatWhisper(string targetNickname, string data);
		void SendRoomListRequest(string data);
		void SendExitRequest(string data);

		string nickname;
		SOCKET clientSocket;
	};
}