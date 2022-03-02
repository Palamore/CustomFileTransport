#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <direct.h>
#include <io.h>
#include <fstream>
using namespace std;

static class Debug
{
public:
	static void Log(string str);

	static void LogError(string str);

	static void LogWarning(string str);
};