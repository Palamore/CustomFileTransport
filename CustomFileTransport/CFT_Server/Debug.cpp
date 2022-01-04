#include "Debug.h"

void Debug::Log(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	cout << (std::ctime(&end_time)) << "[Log] " << str << endl;
}

void Debug::LogError(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	cout << (std::ctime(&end_time)) << "[Error] " << str << endl;
}

void Debug::LogWarning(string str)
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	cout << (std::ctime(&end_time)) << "[Warning] " << str << endl;
}