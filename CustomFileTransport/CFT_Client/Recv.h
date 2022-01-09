#pragma once
#include "IncludeDefineNamespace.h"

namespace Recv
{
	class Network_Recv
	{
	public:

		bool OnRecvPacket(std::string msg);
		bool OnRecvLoginRequest(std::string data);
		bool OnRecvRequestFail(std::string data);
		bool OnRecvChatNormal(std::string data);
		bool OnRecvChatWhisper(std::string data);
		bool OnRecvUserListRequest(std::string data);
		bool OnRecvExitRequest(std::string data);


		std::string nickname;
		SOCKET clientSocket;
	};

}