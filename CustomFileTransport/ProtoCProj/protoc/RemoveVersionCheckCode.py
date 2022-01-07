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

ClientInfoProtoFile = "ClientInfo.pb.h"
PacketTagProtoFile = "PacketTag.pb.h"

RemoveTargetFile = open("C:\CustomFileTransport\CustomFileTransport\ProtoCProj\protoc\TargetRemoveText.txt", 'r')
RemoveTargetText = RemoveTargetFile.read()
RemoveTargetFile.close()

targetPath = ClientPath + ClientInfoProtoFile

TryRemove(ClientPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ClientPath + PacketTagProtoFile, RemoveTargetText)
TryRemove(ServerPath + ClientInfoProtoFile, RemoveTargetText)
TryRemove(ServerPath + PacketTagProtoFile, RemoveTargetText)

print("done")

