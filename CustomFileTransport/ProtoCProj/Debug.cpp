#include "Debug.h"

string GetCurrentDay()
{
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	string year = to_string(t.tm_year + 1900);
	int mon = t.tm_mon + 1;
	string month = "";
	if (mon < 10)
		month = "0" + to_string(mon);
	else
		month = to_string(mon);
	int da = t.tm_mday;
	string day = "";
	if (da < 10)
		day = "0" + to_string(da);
	else
		day = to_string(da);
	return (year + "_" + month + "_" + day);
}

void Debug::Log(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	string log = "";
	log = string(std::ctime(&end_time)) + string("[Log] ") + str + "\n";
	printf("%s ", log.c_str());

	ofstream logFile(GetCurrentDay() + ".txt", ios::app);
	logFile.write(log.c_str(), log.length());
	//logFile << log << endl;
	logFile.close();
}

void Debug::LogError(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	string log = "";
	log = string(std::ctime(&end_time)) + string("[Error] ") + str + "\n";
	cout << log;

	ofstream logFile(GetCurrentDay() + ".txt", ios::app);
	logFile << log << endl;
	logFile.close();
}

void Debug::LogWarning(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	string log = "";
	log = string(std::ctime(&end_time)) + string("[Warning] ") + str + "\n";
	cout << log;

	ofstream logFile(GetCurrentDay() + ".txt", ios::app);
	logFile << log << endl;
	logFile.close();
}