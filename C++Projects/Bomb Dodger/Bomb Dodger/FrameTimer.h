#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include "stdafx.h"
#include <Windows.h>

class FrameTimer
{
private:
	LARGE_INTEGER start_;
	LARGE_INTEGER end_;

	static LARGE_INTEGER kFrequency;
	static bool kIsInitialized;
	bool isSwitch_; // Switch between starting recording a frame to ending a frame's recording
	double time_; 
	double elapsed_time_;

	void Start();
	void End();

public:
	void set_time(double time) { time_ = time; }
	double get_time() { return time_; }
	void set_elapsed_time(double time) { elapsed_time_ = time; }
	double get_elapsed_time() { return elapsed_time_; }

	FrameTimer(double time);
	~FrameTimer() {};
	double GetDeltaSeconds();
	bool IsTimerOver();
};

#endif // !FRAMETIMER_H
