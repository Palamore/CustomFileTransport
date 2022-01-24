#pragma once
#include <string>
#include <vector>
#include <map>

#define METADATA_FILENAME "FileName"
#define METADATA_FILESIZE "FileSize"
#define METADATA_CONTENTSLENGTH "ContentsLength"
#define METADATA_PAYLOADSIZE "PayloadSize"
using namespace std;

static class CommonTools
{
public:
	static string MakeMetaString(string fileName, int fileSize, int contentsLength, int payloadSize);
	static map<string, string> ParseMetaString(string metaStr);
	static vector<string> Split(string targetStr, char splitter);
};
