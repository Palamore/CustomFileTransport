@echo off

cd C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc

set ClientPath=C:\CustomFileTransport\CustomFileTransport\CFT_Client
set ServerPath=C:\CustomFileTransport\CustomFileTransport\CFT_Server
protoc --cpp_out=%ClientPath% ClientInfo.proto
protoc --cpp_out=%ClientPath% PacketTag.proto
protoc --cpp_out=%ServerPath% ClientInfo.proto
protoc --cpp_out=%ServerPath% PacketTag.proto

pause
