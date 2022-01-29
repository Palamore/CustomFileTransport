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
	template <typename T>
	static bool Remove(vector<T>& targetVect, T element);
};


template <typename T>
bool CommonTools::Remove(vector<T>& targetVect, T element)
{
	for (int i = 0; i < targetVect.size(); i++)
	{
		if (targetVect[i] == element)
		{
			targetVect.erase(targetVect.begin() + i);
			return true;
		}
	}
	return false;
}