#include "Send.h"

namespace Send
{

	void Network_Send::SendPacket(string serializedPacket)
	{
		int sendResult = send(clientSocket, serializedPacket.c_str(), strlen(serializedPacket.c_str()), 0);
		if (sendResult == -1) {
			std::cout << "Error : " << WSAGetLastError() << std::endl;
			return;
		}
	}

	void Network_Send::SendLoginRequest(string data)
	{
		PacketTag::LoginRequest loginData;
		loginData.set_nickname(nickname);
		loginData.set_data(data);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::LOGIN_REQUEST);
		packet.set_data(loginData.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		cout << "[LOGIN_REQUEST]" << endl;
	}

	void Network_Send::SendChatNormal(string msg)
	{
		PacketTag::ChatNormal chatData;
		chatData.set_data(msg);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::CHAT_NORMAL);
		packet.set_data(chatData.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		std::cout << "[CHAT_NORMAL]" << std::endl <<
			msg << std::endl;
	}

	void Network_Send::SendChatWhisper(string targetNickname, string data)
	{
		PacketTag::ChatWhisper chatData;
		chatData.set_targetnickname(targetNickname);
		chatData.set_data(data);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::CHAT_WHISPER);
		packet.set_data(chatData.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		std::cout << "[CHAT_WHISPER]" << std::endl <<
			"to " << targetNickname << " : " << data << std::endl;
	}

	void Network_Send::SendRoomListRequest(string data)
	{
		PacketTag::UserListRequest roomList;
		roomList.set_data(data);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::USER_LIST_REQUEST);
		packet.set_data(roomList.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		cout << "[ROOM_USER_LIST]" << endl;
	}

	void Network_Send::SendExitRequest(string data)
	{
		PacketTag::ExitRequest exitReq;
		exitReq.set_data(data);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::EXIT_REQUEST);
		packet.set_data(exitReq.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		cout << "[EXIT_REQUEST]" << endl;
	}

}