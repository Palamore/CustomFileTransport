#pragma once
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <string>
#include "ProtocolTag.h"
#include "ClientInfo.pb.h"
#include "PacketTag.pb.h"
#include "Send.h"

using namespace ServerPacket;
using namespace PacketTag;
using namespace std;
using namespace Send;
#define	MAX_BUFFER		1024
#define SERVER_PORT		8000
#define SERVER_IP		"127.0.0.1"
#define INPUT_COMMAND_INDEX 0
#define INPUT_COMMAND_TYPE_INDEX 1
#define INPUT_TARGET_NICKNAME_INDEX 1
#define INPUT_MESSAGE_INDEX 2