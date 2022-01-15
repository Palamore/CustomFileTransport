@echo off

cd C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc

set ClientPath=C:\CustomFileTransport\CustomFileTransport\CFT_Client
set ServerPath=C:\CustomFileTransport\CustomFileTransport\CFT_Server
set ClientPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Client
set ServerPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Server
protoc --cpp_out=%ClientPath% ClientInfo.proto
protoc --cpp_out=%ClientPath% PacketTag.proto
protoc --cpp_out=%ClientPath_UDP% ClientInfo.proto
protoc --cpp_out=%ClientPath_UDP% PacketTag.proto

protoc --cpp_out=%ServerPath% ClientInfo.proto
protoc --cpp_out=%ServerPath% PacketTag.proto
protoc --cpp_out=%ServerPath_UDP% ClientInfo.proto
protoc --cpp_out=%ServerPath_UDP% PacketTag.proto

pause