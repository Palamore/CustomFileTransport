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

	void Network_Send::SendLoginRequest(string pwd)
	{
		PacketTag::LoginRequest loginData;
		loginData.set_nickname(nickname);
		loginData.set_password(pwd);

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

	void Network_Send::SendUserListRequest(string data)
	{
		PacketTag::UserListRequest roomList;
		roomList.add_data(data);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::USER_LIST_REQUEST);
		packet.set_data(roomList.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		cout << "[ROOM_USER_LIST]" << endl;
	}

	// INPUT_FILENAME_INDEX
	void Network_Send::SendFileSendRequest(std::string fileName)
	{
		ifstream openFile(fileName, ios::binary);
		int length;
		//char* buffer;
		openFile.seekg(0, ios::end);
		length = openFile.tellg();
		openFile.seekg(0, ios::beg);
		//buffer = new char[length];
		//openFile.read(buffer, length);
		openFile.close();

		PacketTag::FileSendRequest sendData;
		sendData.set_filename(fileName);
		sendData.set_filesize(length);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::FILE_SEND_REQUEST);
		packet.set_data(sendData.SerializeAsString());

		SendPacket(packet.SerializeAsString());

		cout << "[SendFileSendRequest] " << fileName << endl;
	}

	void Network_Send::SendAnsFileSendRequest(std::string data)
	{

	}

	void Network_Send::SendExitRequest(string data)
	{
		PacketTag::ExitRequest exitReq;
		exitReq.set_data(data);

		int length = exitReq.ByteSizeLong();
		
		//TODO :: PacktMsg의 data bytes로 수정
		void* buffer = malloc(length);
		exitReq.SerializeToArray(buffer, length);

		PacketTag::PacketMsg packet;
		packet.set_nickname(nickname);
		packet.set_type(PacketTag::PacketType::EXIT_REQUEST);
		packet.set_data(exitReq.SerializeAsString());

		
		SendPacket(packet.SerializeAsString());

		cout << "[EXIT_REQUEST]" << endl;
	}

}