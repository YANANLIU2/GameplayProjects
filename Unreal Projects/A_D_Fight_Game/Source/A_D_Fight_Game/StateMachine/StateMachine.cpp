#include "StateMachine.h"
#include <assert.h>

StateMachine::StateMachine(int max_state)
	: ST_MAX_STATES(max_state)
	, current_state_(0)
	, is_event_generated_(false)
	, p_event_data_(NULL)
{
}

void StateMachine::ExternalEvent(unsigned char new_state, EventData* p_data)
{
	// If the event is supposed to be ignored => deletd the event if any
	if (new_state == ST_IGNORED)
	{
		if (p_data)
		{
			delete p_data;
		}
	}
	else if (new_state == ST_CANNOT_HAPPEN)
	{
		// To do: log error msg here
	}
	else
	{
		// Generates the event, execute the state engine
		InternalEvent(new_state, p_data);
		StateEngine();
	}
}

void StateMachine::InternalEvent(unsigned char new_state, EventData* p_data)
{
	p_event_data_ = p_data;
	is_event_generated_ = true;
	current_state_ = new_state;
}

void StateMachine::StateEngine(void)
{
	EventData* p_data_temp = NULL;
	// Lock mutex here
	mutex_lock_.lock();
	// While events are generated, keep executing states
	while (is_event_generated_)
	{
		// Copy event date pointer
		p_data_temp = p_event_data_;
		// event data used up, reset ptr
		p_event_data_ = NULL;
		// Event used up, reset flag
		is_event_generated_ = false;
		assert(current_state_ < ST_MAX_STATES);
		// Execute the state passing in event data, if any
		const StateStruct* p_state_map = GetStateMap();
		(this->*p_state_map[current_state_].p_state_func)(p_data_temp);
		// If event datta was used, delete it
		if (p_data_temp)
		{
			delete p_data_temp;
			p_data_temp = NULL;
		}
	}
	// Unlock mutex here
	mutex_lock_.unlock();
}
