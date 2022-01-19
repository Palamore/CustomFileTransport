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


/// <summary>
/// 메타파일 작성시 Reliable UDP를 활용한다면 필요한 정보는
/// 파일의 내용 분할 시 분할 숫자.
/// 서버가 받아야 하는 페이로드의 갯수가 필요하다.
/// </summary>
string CommonTools::MakeMetaString(string fileName, int fileSize, int contentsLength, int payloadSize)
{ 
	string metaStr = "";
	metaStr += "FileName";
	metaStr += '\n';
	metaStr += fileName;
	metaStr += '\n';
	metaStr += "FileSize";
	metaStr += '\n';
	metaStr += to_string(fileSize);
	metaStr += '\n';
	metaStr += "ContentsLength";
	metaStr += '\n';
	metaStr += to_string(contentsLength);
	metaStr += '\n';
	metaStr += "PayloadSize";
	metaStr += '\n';
	metaStr += to_string(payloadSize);
	return metaStr;
}

map<string, string> CommonTools::ParseMetaString(string metaStr)
{
	metaStr = Trim(metaStr);
	map<string, string> data;
	vector<string> splitted = Split(metaStr, '\n');

	for (int i = 0; i < splitted.size() - 1; i++)
	{
		if (splitted[i]._Equal("FileName"))
		{
			data.insert({ splitted[i], splitted[i + 1] });
			i++;
		}
		if (splitted[i]._Equal("FileSize"))
		{
			data.insert({ splitted[i], splitted[i + 1] });
			i++;
		}
		if (splitted[i]._Equal("ContentsLength"))
		{
			data.insert({ splitted[i], splitted[i + 1] });
			i++;
		}
		if (splitted[i]._Equal("PayloadSize"))
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
