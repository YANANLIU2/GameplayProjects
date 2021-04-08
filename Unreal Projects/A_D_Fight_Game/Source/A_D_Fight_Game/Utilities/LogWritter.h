#pragma once
// UE4 
#include "Engine.h"
#include "Containers/UnrealString.h"

#include <fstream>
#include <string>
#include <Windows.h>

DECLARE_LOG_CATEGORY_EXTERN(LogCustom, Log, All);

class LogWritter
{
	// enum for LOG_TYPE
	enum class ELogType
	{
		kNoLog = 1,
		kConsole, // UE_LOGGING
		kFileLog
	};

public:
	// Singleton Pattern
	static LogWritter& get_instance()
	{
		static LogWritter instance;
		return instance;
	}

	// Interface to control log levels
	inline void EnableConsoleLogging() { log_type_ = ELogType::kConsole; }
	inline void EnableFileLogging() { log_type_ = ELogType::kFileLog; }
	void LogIntoFile(const char*);
	void LogOnConsole(FString);

private:
	LogWritter();
	~LogWritter();
	LogWritter(const LogWritter&) = delete;
	LogWritter& operator=(const LogWritter&) = delete;
	std::string get_current_time();

private:
	std::ofstream file_;
	ELogType log_type_;
};




