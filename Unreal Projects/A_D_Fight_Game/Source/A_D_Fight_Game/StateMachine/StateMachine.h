#pragma once
#include <stdio.h>
#include <mutex>          // std::mutex
#include "EventData.h"

struct StateStruct;
class StateMachine
{
public:
	StateMachine(int max_states);
	virtual ~StateMachine() {};

protected:
	enum
	{
		ST_IGNORED = 0xFE, // 254
		ST_CANNOT_HAPPEN, //255
	};

	unsigned char current_state_;
	// Generates an external event
	void ExternalEvent(unsigned char, EventData* = NULL);
	// Generates an internal event
	void InternalEvent(unsigned char, EventData* = NULL);
	virtual const StateStruct* GetStateMap() = 0;

private: 
	const int ST_MAX_STATES;
	bool is_event_generated_;
	EventData* p_event_data_;
	std::mutex mutex_lock_;           
	void StateEngine(void);
};

typedef void (StateMachine::* StateFunc)(EventData*);

struct StateStruct //Wrapper
{
	StateFunc p_state_func;
};

// Starts the state map sequence
#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct kStateMap[] = { 

// Has an argument a state function
#define STATE_MAP_ENTRY(entry)\
    { reinterpret_cast<StateFunc>(entry) },

// Terminates the map
#define END_STATE_MAP \
    { reinterpret_cast<StateFunc>(NULL) }\
    }; \
    return &kStateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char kTRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    ExternalEvent(kTRANSITIONS[current_state_], data);
