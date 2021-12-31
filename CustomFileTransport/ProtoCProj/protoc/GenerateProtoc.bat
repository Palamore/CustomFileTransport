@echo off

cd C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc

protoc --cpp_out=C:\CustomFileTransport\CustomFileTransport\CFT_Client ClientInfo.proto
protoc --cpp_out=C:\CustomFileTransport\CustomFileTransport\CFT_Client PacketTag.proto
protoc --cpp_out=C:\CustomFileTransport\CustomFileTransport\CFT_Server ClientInfo.proto
protoc --cpp_out=C:\CustomFileTransport\CustomFileTransport\CFT_Server PacketTag.proto

pause
