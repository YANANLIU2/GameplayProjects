#include "stdafx.h"
#include "FrameTimer.h"

LARGE_INTEGER FrameTimer::kFrequency = { 0 };
bool FrameTimer::kIsInitialized = false;

FrameTimer::FrameTimer(double time)
	: time_(time)
	, start_({ 0 })
	, end_({ 0 })
	, isSwitch_(true)
	, elapsed_time_(0)
{
	if (!kIsInitialized)
	{
		QueryPerformanceFrequency(&kFrequency);
		kIsInitialized = true;
	}
}

void FrameTimer::Start()
{
	QueryPerformanceCounter(&start_);
}

void FrameTimer::End()
{
	QueryPerformanceCounter(&end_);
}

double FrameTimer::GetDeltaSeconds()
{
	LARGE_INTEGER delta;
	delta.QuadPart = end_.QuadPart - start_.QuadPart;
	double result = ((double)delta.QuadPart / (double)kFrequency.QuadPart);
	return result ;
}

bool FrameTimer::IsTimerOver()
{
	// record time
	if (isSwitch_ == true)
	{
		Start();
		isSwitch_ = false;
	}
	else
	{
		End();
		isSwitch_ = true;
	}

	// calcualte and comapre
	double delta = GetDeltaSeconds();
	delta = delta < 0 ? 0 : delta;
	elapsed_time_ += delta;

	if (elapsed_time_ > time_)
	{
		elapsed_time_ -= time_;
		return true;
	}
	return false;
}

