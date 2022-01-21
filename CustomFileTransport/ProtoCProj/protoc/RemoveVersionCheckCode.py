import fileinput


def TryRemove(targetFilePath, RemoveTargetText) :
    targetFileOpen = open(targetFilePath, 'r')
    targetFileText = targetFileOpen.read()
    targetFileOpen.close()
    result = targetFileText.replace(RemoveTargetText, "")
    targetFileOpen = open(targetFilePath, 'w')
    targetFileOpen.write(result)
    targetFileOpen.close()


ClientPath = "C:/CustomFileTransport/CustomFileTransport/CFT_Client/"
ServerPath = "C:/CustomFileTransport/CustomFileTransport/CFT_Server/"
ClientUDPPath = "C:/CustomFileTransport/CustomFileTransport/CFT_UDP_Client/"
ServerUDPPath = "C:/CustomFileTransport/CustomFileTransport/CFT_UDP_Server/"

ClientInfoProtoFile = "ClientInfo.pb.h"
PacketTagProtoFile = "PacketTag.pb.h"
UDPProtoFile = "UDPFileSend.pb.h"

RemoveTargetFile = open("C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc\TargetRemoveText.txt", 'r')
RemoveTargetText = RemoveTargetFile.read()
RemoveTargetFile.close()

targetPath = ClientPath + ClientInfoProtoFile

TryRemove(ClientPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ClientPath + PacketTagProtoFile, RemoveTargetText)
TryRemove(ServerPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ServerPath + PacketTagProtoFile, RemoveTargetText)

TryRemove(ClientUDPPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ClientUDPPath + PacketTagProtoFile, RemoveTargetText)
TryRemove(ClientUDPPath + UDPProtoFile, RemoveTargetText)
TryRemove(ServerUDPPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ServerUDPPath + PacketTagProtoFile, RemoveTargetText)
TryRemove(ServerUDPPath + UDPProtoFile, RemoveTargetText)



print("done")

