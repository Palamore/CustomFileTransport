#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

static class Debug
{
public:
	static void Log(string str);

	static void LogError(string str);

	static void LogWarning(string str);
};