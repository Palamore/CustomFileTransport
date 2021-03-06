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
		case PacketType::FILE_SEND_REQUEST:
			if (!OnRecvFileSendRequest(packet.data()))
			{
				return false;
			}
			break;
		case PacketType::FILE_SEND_REQUEST_ANSWER:
			if (!OnRecvFileSendRequestAnswer(packet.data()))
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
		if (!loginData.ParseFromString(data))
		{
			Debug::LogError("loginData Parsing Failed");
			return false;
		}

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
		if (!failData.ParseFromString(data))
		{
			Debug::LogError("failData Parsing Failed");
			return false;
		}

		Debug::Log("Request Failed : " + failData.data());
		return true;
	}

	bool Network_Recv::OnRecvChatNormal(std::string data)
	{
		AnsChatNormal chatData;
		if (!chatData.ParseFromString(data))
		{
			Debug::LogError("chatData Parsing Failed");
			return false;
		}

		cout << chatData.nickname() << " : " << chatData.data() << endl;

		return true;
	}

	bool Network_Recv::OnRecvChatWhisper(std::string data)
	{
		AnsChatWhisper chatData;
		if (!chatData.ParseFromString(data))
		{
			Debug::LogError("chatData Parsing Failed");
			return false;
		}

		cout << chatData.nickname() << " : " << chatData.data() << endl;

		return true;
	}

	bool Network_Recv::OnRecvUserListRequest(std::string data)
	{
		AnsUserListRequest listData;
		if (!listData.ParseFromString(data))
		{
			Debug::LogError("listData Parsing Failed");
			return false;
		}

		cout << "--------User List--------" << endl;
		for (int i = 0; i < listData.data_size(); i++)
		{
			cout << listData.data(i) << endl;
		}

		return true;
	}

	bool Network_Recv::OnRecvFileSendRequest(std::string data)
	{
		FileSendRequest fileData;
		if (!fileData.ParseFromString(data))
		{
			Debug::LogError("fileData Parsing Failed");
			return false;
		}
		// TODO :: ???? ?? UDP ???????? ????. ???? ?????? ???? Answer ???? ????
		// ???? ?????? ???????? ?????? ?????

		return true;
	}

	bool Network_Recv::OnRecvFileSendRequestAnswer(std::string data)
	{
		AnsFileSendRequest ansData;
		if (!ansData.ParseFromString(data))
		{
			Debug::LogError("ansData Parsing Failed");
			return false;
		}
		// ???????? ???????? ?????? ?????
		ofstream metaFile(METAFILE_PATH);
		string metaStr = ansData.data();
		metaFile.clear();
		metaFile << metaStr;
		metaFile.close();
		

		ShellExecute(NULL, TEXT("open"), TEXT(UDP_CLIENT_PATH), NULL, NULL, SW_SHOW);


		return true;
	}

	bool Network_Recv::OnRecvExitRequest(std::string data)
	{
		AnsExitRequest exitData;
		if (!exitData.ParseFromString(data))
		{
			Debug::LogError("exitData Parsing Failed");
			return false;
		}

		cout << "Logout result : " << exitData.data() << endl;

		return true;
	}

}