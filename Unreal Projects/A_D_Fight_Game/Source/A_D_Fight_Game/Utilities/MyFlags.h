#pragma once
#include "ProjectSettings.h"
#define ALL_FLAGS_ON 0XFFFFFFFF
#define ALL_FLAGS_FF 0X00000000
#define LAST_FLAG_ON 0X00000001 

// The class is to provide a flags class to easier manage flags
class MyFlags
{
	uint32_t  flags_;

public:
	// Constructor
	MyFlags(): flags_() {}

	// Destructor
	~MyFlags() = default;

	// Get the flags
	uint32_t get_flags() { return flags_; }

	// To get a single bit at the index in the flags
	uint32_t operator[](size_t index) { return (flags_ >> index) & LAST_FLAG_ON; }

	// Turn on some flags
	void TurnOnFlags(uint32_t targetFlags) { flags_ |= targetFlags; }

	// Turn off some flags
	void TurnOffFlags(uint32_t targetFlags) { flags_ &= ~targetFlags; }

	// Whether the target flags are on or not
	bool IsFlagsOn(uint32_t flags) { return (flags & flags_) > ALL_FLAGS_FF; }
};
