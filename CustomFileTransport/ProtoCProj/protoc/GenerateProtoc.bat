@echo off

cd C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc

set ClientPath=C:\CustomFileTransport\CustomFileTransport\CFT_Client
set ServerPath=C:\CustomFileTransport\CustomFileTransport\CFT_Server
set ClientPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Client
set ServerPath_UDP=C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Server
set ClientPath_ASIO=C:\CustomFileTransport\CustomFileTransport\CFT_ASIO_Client
set ServerPath_ASIO=C:\CustomFileTransport\CustomFileTransport\CFT_ASIO_Server
set ProtoCPath=C:\CustomFileTransport\CustomFileTransport\ProtoCProj

protoc --cpp_out=%ProtoCPath% ClientInfo.proto
protoc --cpp_out=%ProtoCPath% PacketTag.proto
protoc --cpp_out=%ProtoCPath% UDPFileSend.proto

pause