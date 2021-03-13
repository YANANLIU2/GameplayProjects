#pragma once

#include <CoreWindow.h>

class MyLog
{
	// Console handler
	HANDLE h_console_;

	// Constructor
	MyLog() = default;

public:
	// Singleton Pattern
	static MyLog& get_instance()
	{
		static MyLog instance_;
		return instance_;
	}

	MyLog(MyLog const&) = delete;

	void operator=(MyLog const&) = delete;

	// Initialization
	void Init();

	// Destructor
	~MyLog() = default;

	// Log
	void LogToConsole(const char* string);
};

