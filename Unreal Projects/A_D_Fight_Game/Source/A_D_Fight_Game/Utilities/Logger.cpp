// C++ header files
#include <iostream>
#include <cstdlib>
#include <ctime>

// Code specific header files
#include "Logger.h"

// Log File name, File name should be change from here only
const std::string kLogFileName = "MyLogFile.log";
const int kCurrentTimeBufferSize = 26;

#define LOG(log_level)							   \
	if(true){									   \
		std::string data;						   \
		data.append(log_level);					   \
		data.append(text);						   \
		if (log_type_ == ELogType::kFileLog)	   \
		{										   \
			LogIntoFile(data);					   \
		}										   \
		else                                       \
		{										   \
			LogOnConsole(data);                    \
		}										   \
	} else                                         \
		(void)0;								   
												   
#define LOG_CHECK(log_level, check_log_level)			   				\
	if(true){									   \
		std::string data;						   \
		data.append(log_level);					   \
		data.append(text);						   \
		if(log_level_ >= check_log_level)		  \
		{										  \
			if (log_type_ == ELogType::kFileLog)  \
			{									  \
				LogIntoFile(data);				  \
			}									  \
			else								  \
			{									  \
				LogOnConsole(data);				  \
			}									  \
												  \
		}										  \
	} else                                        \
		(void)0;	

							

Logging::Logger::Logger()
{
	file_.open(kLogFileName.c_str(), std::ios::out | std::ios::app);
	log_level_ = ELogLevel::kLogLevelTrace;
	log_type_ = ELogType::kFileLog;
}

Logging::Logger::~Logger()
{
	file_.close();
}

void Logging::Logger::LogIntoFile(std::string& data)
{
	file_ << get_current_time() << ' ' << data << '\n';
}

void Logging::Logger::LogOnConsole(std::string& data)
{
	std::cout << get_current_time() << ' ' << data << '\n';
}

std::string Logging::Logger::get_current_time()
{
	time_t now = time(0);
	char curret_time[kCurrentTimeBufferSize];
	ctime_s(curret_time, sizeof curret_time, &now);
	// Remove last character '\n' of currrent time
	curret_time[kCurrentTimeBufferSize - 1] = '\0';
	return curret_time;
}

void Logging::Logger::Error(const char* text) throw()
{
	LOG("[ERROR]: ");
}

void Logging::Logger::Error(std::string& text) throw()
{
	Error(text.data());
}

void Logging::Logger::Error(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Error(text.data());
}

void Logging::Logger::Alarm(const char* text) throw()
{
	LOG("[Alarm]: ");
}

void Logging::Logger::Alarm(std::string& text) throw()
{
	Alarm(text.data());
}

void Logging::Logger::Alarm(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Alarm(text.data());
}

void Logging::Logger::Always(const char* text) throw()
{
	LOG("[Always]: ");
}

void Logging::Logger::Always(std::string& text) throw()
{
	Always(text.data());
}

void Logging::Logger::Always(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Always(text.data());
}

void Logging::Logger::Buffer(const char* text) throw()
{
	// Buffer is a special case. Don't add time stamp and log level. Log raw bytes.
	if (log_type_ == ELogType::kConsole)
	{
		if (log_level_ >= ELogLevel::kLogLevelBuffer)
		{
			file_ << text << '\n';
		}
	}
	else
	{
		if (log_level_ >= ELogLevel::kLogLevelBuffer)
		{
			std::cout << text << '\n';
		}
	}
}

void Logging::Logger::Buffer(std::string& text) throw()
{
	Buffer(text.data());
}

void Logging::Logger::Buffer(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Buffer(text.data());
}

void Logging::Logger::Info(const char* text) throw()
{
	LOG_CHECK("[Info]: ", ELogLevel::kLogLevelInfo);
}

void Logging::Logger::Info(std::string& text) throw()
{
	Info(text.data());
}

void Logging::Logger::Info(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Info(text.data());
}

void Logging::Logger::Trace(const char* text) throw()
{
	LOG_CHECK("[Trace]: ", ELogLevel::kLogLevelTrace);
}

void Logging::Logger::Trace(std::string& text) throw()
{
	Trace(text.data());
}

void Logging::Logger::Trace(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Trace(text.data());
}

void Logging::Logger::Debug(const char* text) throw()
{
	LOG_CHECK("[Debug]: ", ELogLevel::kLogLevelDebug);
}

void Logging::Logger::Debug(std::string& text) throw()
{
	Debug(text.data());
}

void Logging::Logger::Debug(std::ostringstream& stream) throw()
{
	std::string text = stream.str();
	Debug(text.data());
}
