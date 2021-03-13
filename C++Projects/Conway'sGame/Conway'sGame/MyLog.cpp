#include "stdafx.h"
#include "MyLog.h"
#include <iostream>
#include <cassert>

void MyLog::Init()
{
	AllocConsole();

	h_console_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

void MyLog::LogToConsole(const char* string)
{
	size_t len = strlen(string);

	assert(len < 100);

	DWORD writtenCount;

	wchar_t output[101];

	swprintf_s(output, L"%hs\n", string);

	// Draw one extra character for inserted newline!
	BOOL result = WriteConsole(h_console_, output, (DWORD)(strlen(string) + 1), &writtenCount, nullptr);
}
