#include "stdafx.h"
#include "Input.h"
#include "MyMath.h"

Input::Input()
{
	// Initialize the inputs vector
	for (size_t i = 0; i < (size_t)EInputValue::kInputsNum; i++)
	{
		inputs_.push_back(std::make_pair((EInputValue)i, EInputState::kRelease));
	}
}

void Input::Reset()
{
	// Reset all inputs to release state
	for (size_t i = 0; i < (size_t)EInputValue::kInputsNum; i++)
	{
		inputs_[i].second = EInputState::kRelease;
	}
}

Input::EInputState Input::get_input_state(EInputValue value) const
{
	return inputs_[(size_t)value].second;
}

void Input::SetInputValue(EInputValue input, EInputState value)
{
	inputs_[(size_t)input].second = value;
}

void Input::Update()
{
	// Loop all inputs: kJustRelease => kRelease
	for (size_t i = 0; i < (size_t)EInputValue::kInputsNum; i++)
	{
		if (inputs_[i].second == EInputState::kJustRelease)
		{
			inputs_[i].second = EInputState::kRelease;
		}
	}
}

