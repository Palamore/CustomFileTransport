#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
using namespace std;

static class Debug
{
public:
	static void Log(string str);

	static void LogError(string str);

	static void LogWarning(string str);
};