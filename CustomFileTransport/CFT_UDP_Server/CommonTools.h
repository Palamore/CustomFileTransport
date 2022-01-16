#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

static class CommonTools
{
public:
	static string MakeMetaString(string fileName, int fileSize);
	static map<string, string> ParseMetaString(string metaStr);
	static vector<string> Split(string targetStr, char splitter);
};
