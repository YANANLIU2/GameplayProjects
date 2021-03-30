#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>

namespace Logging
{
	#define LOG_ERROR(x) Logger::get_instance()->Error(x);
	#define LOG_ALARM(x) Logger::get_instance()->Alarm(x);
	#define LOG_ALWAYS(x) Logger::get_instance()->Always(x);
	#define LOG_INFO(x) Logger::get_instance()->Info(x);
	#define LOG_BUFFER(x) Logger::get_instance()->Buffer(x);
	#define LOG_TRACE(x) Logger::get_instance()->Trace(x);
	#define LOG_DEBUG(x) Logger::get_instance()->Debug(x);

	class Logger
	{
		// enum for LOG_LEVEL
		enum class ELogLevel
		{
			kDisableLog = 1,
			kLogLevelInfo,
			kLogLevelBuffer,
			kLogLevelTrace,
			kLogLevelDebug,
			kEnableLog
		};

		// enum for LOG_TYPE
		enum class ELogType
		{
			kNoLog = 1,
			kConsole,
			kFileLog
		};

	public:
		// Singleton Pattern
		static Logger& get_instance()
		{
			static Logger instance;
			return instance;
		}
		
		// Interface for error log
		void Error(const char*) throw();
		void Error(std::string &) throw();
		void Error(std::ostringstream &) throw();
		
		// Interface for alarm log
		void Alarm(const char*) throw();
		void Alarm(std::string&) throw();
		void Alarm(std::ostringstream&) throw();

		// Interface for always log
		void Always(const char*) throw();
		void Always(std::string&) throw();
		void Always(std::ostringstream&) throw();

		// Interface for buffer log
		void Buffer(const char*) throw();
		void Buffer(std::string&) throw();
		void Buffer(std::ostringstream&) throw();

		// Interface for info log
		void Info(const char*) throw();
		void Info(std::string&) throw();
		void Info(std::ostringstream&) throw();

		// Interface for trace log
		void Trace(const char*) throw();
		void Trace(std::string&) throw();
		void Trace(std::ostringstream&) throw();

		// Interface for debug log
		void Debug(const char*) throw();
		void Debug(std::string&) throw();
		void Debug(std::ostringstream&) throw();

		// Interface to control log levels
		inline void set_log_type(ELogType type) { log_type_ = type; }
		inline void EnableConsoleLogging() { log_type_ = ELogType::kConsole; }
		inline void EnableFileLogging() { log_type_ = ELogType::kFileLog; }

	private:
		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		void LogIntoFile(std::string& data);
		void LogOnConsole(std::string& data);
		std::string get_current_time();

	private:
		std::ofstream file_;
		ELogType log_type_;
		ELogLevel log_level_;
	};
}




