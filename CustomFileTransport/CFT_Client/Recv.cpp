#include "Recv.h"
#include "Debug.h"

using namespace PacketTag;

namespace Recv
{
	bool Network_Recv::OnRecvPacket(std::string msg)
	{
		PacketMsg packet;
		packet.ParseFromString(msg);

		switch (packet.type())
		{
		case PacketType::LOGIN_REQUEST:
			if (!OnRecvLoginRequest(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::REQUEST_FAIL:
			if (!OnRecvRequestFail(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::CHAT_NORMAL:
			if(!OnRecvChatNormal(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::CHAT_WHISPER:
			if(!OnRecvChatWhisper(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::USER_LIST_REQUEST:
			if(!OnRecvUserListRequest(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::EXIT_REQUEST:
			if(!OnRecvExitRequest(packet.data()))
			{
				return false;
			}
			break;
		}

		return true;
	}

	bool Network_Recv::OnRecvLoginRequest(std::string data)
	{
		AnsLoginRequest loginData;
		loginData.ParseFromString(data);

		switch (loginData.type())
		{
		case LoginResultType::LOGIN_SUCCESS:
			nickname = loginData.nickname();
			break;
		case LoginResultType::LOGIN_FAIL:
			Debug::LogError("Login Failed : " + loginData.data());
			return false;
		}

		return true;
	}

	bool Network_Recv::OnRecvRequestFail(std::string data)
	{
		AnsRequestFail failData;
		failData.ParseFromString(data);

		Debug::Log("Request Failed : " + failData.data());
		return true;
	}

	bool Network_Recv::OnRecvChatNormal(std::string data)
	{
		AnsChatNormal chatData;
		chatData.ParseFromString(data);

		cout << chatData.nickname() << " : " << chatData.data() << endl;

		return true;
	}

	bool Network_Recv::OnRecvChatWhisper(std::string data)
	{
		AnsChatWhisper chatData;
		chatData.ParseFromString(data);

		cout << chatData.nickname() << " : " << chatData.data() << endl;

		return true;
	}

	bool Network_Recv::OnRecvUserListRequest(std::string data)
	{
		AnsUserListRequest listData;
		listData.ParseFromString(data);

		cout << "--------User List--------" << endl;
		for (int i = 0; i < listData.data_size(); i++)
		{
			cout << listData.data(i) << endl;
		}

		return true;
	}

	bool Network_Recv::OnRecvExitRequest(std::string data)
	{
		AnsExitRequest exitData;
		exitData.ParseFromString(data);

		cout << "Logout result : " << exitData.data() << endl;

		return false;
	}

}