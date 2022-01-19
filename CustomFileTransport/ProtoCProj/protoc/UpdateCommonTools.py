import shutil

source1='C:\CustomFileTransport\CustomFileTransport\ProtoCProj\CommonTools.h'
source2='C:\CustomFileTransport\CustomFileTransport\ProtoCProj\CommonTools.cpp'
dest1='C:\CustomFileTransport\CustomFileTransport\CFT_Client\CommonTools.h'
dest2='C:\CustomFileTransport\CustomFileTransport\CFT_Client\CommonTools.cpp'

shutil.copyfile(source2, dest2)
shutil.copyfile(source1, dest1)


dest1='C:\CustomFileTransport\CustomFileTransport\CFT_Server\CommonTools.h'
dest2='C:\CustomFileTransport\CustomFileTransport\CFT_Server\CommonTools.cpp'

shutil.copyfile(source2, dest2)
shutil.copyfile(source1, dest1)


dest1='C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Client\CommonTools.h'
dest2='C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Client\CommonTools.cpp'

shutil.copyfile(source2, dest2)
shutil.copyfile(source1, dest1)


dest1='C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Server\CommonTools.h'
dest2='C:\CustomFileTransport\CustomFileTransport\CFT_UDP_Server\CommonTools.cpp'

shutil.copyfile(source2, dest2)
shutil.copyfile(source1, dest1)
