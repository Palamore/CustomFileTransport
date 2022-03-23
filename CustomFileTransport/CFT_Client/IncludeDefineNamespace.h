#pragma once
#include "ProtocolTag.h"
#include "ClientInfo.pb.h"
#include "PacketTag.pb.h"
#include "CommonTools.h"
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <map>
#include <io.h>
using namespace std;

#define	MAX_BUFFER		1024
#define SERVER_PORT		8000
#define UDP_PAYLOAD_SIZE 10000
#define SERVER_IP		"127.0.0.1"
#define PUBLIC_SERVER_IP		"121.134.137.247"
#define INPUT_COMMAND_INDEX 0
#define INPUT_COMMAND_TYPE_INDEX 1
#define INPUT_TARGET_NICKNAME_INDEX 1
#define INPUT_FILENAME_INDEX 1
#define INPUT_MESSAGE_INDEX 2
#define PROJECT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\"
#define UDP_SERVER_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Server.exe"
#define UDP_CLIENT_PATH "C:\\CustomFileTransport\\CustomFileTransport\\x64\\Debug\\CFT_UDP_Client.exe"
#define METAFILE_PATH "C:\\CustomFileTransport\\CustomFileTransport\\tmp\\meta_client.txt"
#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"