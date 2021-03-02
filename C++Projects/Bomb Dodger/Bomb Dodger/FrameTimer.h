#ifndef FRAMETIMER_H
#define FRAMETIMER_H

// The class is for providing a timer 
class FrameTimer
{
private:
	// The start of recording a frame
	LARGE_INTEGER start_;
	
	// The end of recording a frame
	LARGE_INTEGER end_;

	// A frequency then we use that value to determine how many counter ticks will occur each millisecond.
	static LARGE_INTEGER kFrequency;
	
	// Whether all the timers has been intialized or not. It's needed only once.
	static bool kIsInitialized;
	
	// Switch between starting recording a frame to ending a frame's recording
	bool isSwitch_; 

	// The time of one loop of the timer
	double time_; 

	// The elapsed time in the current loop
	double elapsed_time_;

	// Start recording 
	void Start();

	// End recording 
	void End();

	// Get the passed time from start to end
	double GetDeltaSeconds();

public:
	// Constructor
	FrameTimer(double time);

	// Destructor
	~FrameTimer() = default;

	// Set the time of one loop of the timer
	void set_time(double time) { time_ = time; }

	// Get the time of one loop of the timer
	double get_time() { return time_; }

	// Set the elapsed time in the current loop
	void set_elapsed_time(double time) { elapsed_time_ = time; }
	
	// Get the elapsed time in the current loop
	double get_elapsed_time() { return elapsed_time_; }

	// Update the timer. If a loop ends start a new loop
	bool UpdateLoopTimer();

	// Update the timer only if a loop hasn't ended
	bool UpdateTimer();

	// Restart the timer 
	void RestartTimer() { elapsed_time_ -= time_; }
};
#endif // !FRAMETIMER_H
