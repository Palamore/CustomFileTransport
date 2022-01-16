#include "CommonTools.h"

string CommonTools::MakeMetaString(string fileName, int fileSize)
{
	string metaStr = "";
	metaStr += "Filename";
	metaStr += '\n';
	metaStr += fileName;
	metaStr += '\n';
	metaStr += "Filesize";
	metaStr += '\n';
	metaStr += to_string(fileSize);
	return metaStr;
}

map<string, string> CommonTools::ParseMetaString(string metaStr)
{
	map<string, string> data;
	vector<string> splitted = Split(metaStr, '\n');
	
	for (int i = 0; i < splitted.size() - 1 ; i++)
	{
		
		if (splitted[i]._Equal("Filename"))
		{
			data.insert({ splitted[i], splitted[i + 1] });
			i++;
		}
		if (splitted[i]._Equal("Filesize"))
		{
			data.insert({ splitted[i], splitted[i + 1] });
			i++;
		}
	}
	return data;
}

vector<string> CommonTools::Split(string targetStr, char splitter)
{
	vector<string> vect;
	string e = "";
	for (int i = 0; i < targetStr.size(); i++)
	{
		if (targetStr[i] == splitter)
		{
			vect.push_back(e);
			e = "";
		}
		else
		{
			e += targetStr[i];
		}
	}
	vect.push_back(e);
	return vect;
}
