#include "CommonTools.h"

string Trim(string str)
{
	int count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '\r')
		{
			for (int j = i; j < str.length() - 1; j++)
			{
				str[j] = str[j + 1];
			}
			count++;
		}
	}
	for (int i = str.length() - 1; i > str.length() - count; i--)
	{
		str[i] = '\0';
	}
	return str;
}

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
	metaStr = Trim(metaStr);
	map<string, string> data;
	vector<string> splitted = Split(metaStr, '\n');

	for (int i = 0; i < splitted.size() - 1; i++)
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
