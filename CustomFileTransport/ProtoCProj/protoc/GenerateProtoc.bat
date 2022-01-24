@echo off

cd C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc

set ClientPath=C:\CustomFileTransport\CustomFileTransport\CFT_Client
set ServerPath=C:\CustomFileTransport\CustomFileTransport\CFT_Server
set ClientPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Client
set ServerPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Server
set ClientPath_ASIO=C:\CustomFileTransport\CustomFileTransport\CFT_ASIO_Client
set ServerPath_ASIO=C:\CustomFileTransport\CustomFileTransport\CFT_ASIO_Server

protoc --cpp_out=%ClientPath% ClientInfo.proto
protoc --cpp_out=%ClientPath% PacketTag.proto
protoc --cpp_out=%ClientPath_UDP% ClientInfo.proto
protoc --cpp_out=%ClientPath_UDP% PacketTag.proto
protoc --cpp_out=%ClientPath_ASIO% ClientInfo.proto
protoc --cpp_out=%ClientPath_ASIO% PacketTag.proto

protoc --cpp_out=%ServerPath% ClientInfo.proto
protoc --cpp_out=%ServerPath% PacketTag.proto
protoc --cpp_out=%ServerPath_UDP% ClientInfo.proto
protoc --cpp_out=%ServerPath_UDP% PacketTag.proto
protoc --cpp_out=%ServerPath_ASIO% ClientInfo.proto
protoc --cpp_out=%ServerPath_ASIO% PacketTag.proto


protoc --cpp_out=%ClientPath_UDP% UDPFileSend.proto
protoc --cpp_out=%ServerPath_UDP% UDPFileSend.proto

pause