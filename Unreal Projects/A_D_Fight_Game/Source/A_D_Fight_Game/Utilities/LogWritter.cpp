// Code specific header files
#include "LogWritter.h"

// Log File name, File name should be change from here only
const std::string kLogFileName = "MyLogFile.log";
const int kCurrentTimeBufferSize = 26;

DEFINE_LOG_CATEGORY(LogCustom);

LogWritter::LogWritter()
{
	file_.open(kLogFileName.c_str(), std::ios::out | std::ios::app);
	log_type_ = ELogType::kConsole;
}

LogWritter::~LogWritter()
{
	file_.close();
}

void LogWritter::LogIntoFile(const char* data)
{
	file_ << get_current_time() << ' ' << data << '\n';
}

void LogWritter::LogOnConsole(FString data)
{
	UE_LOG(LogCustom, Warning, TEXT("%s"), *data);
}

std::string LogWritter::get_current_time()
{
	time_t now = time(0);
	char curret_time[kCurrentTimeBufferSize];
	ctime_s(curret_time, sizeof curret_time, &now);
	// Remove last character '\n' of currrent time
	curret_time[kCurrentTimeBufferSize - 1] = '\0';
	return curret_time;
}
