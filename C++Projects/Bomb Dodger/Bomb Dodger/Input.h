#pragma once
#include <utility>      // std::pair, std::make_pair
#include <vector>
using std::vector;
using std::pair;

//  The class is for recording player input and providing the values to other objects
class Input
{
public:
	// Input value types 
	enum class EInputValue
	{
		kQuit,
		kSkip,
		kIsMovingUp,
		kIsMovingDown,
		kIsMovingLeft,
		kIsMovingRight,
		kAttackRight,
		kAttackDown,
		kAttackLeft,
		kAttackUp,
		kInputsNum
	};

	// Input value states
	enum class EInputState
	{
		kPress,
		kJustRelease,
		kRelease,
	};

	// The mapping of input values and their states, like a keyboard mapping
	vector<pair<EInputValue, EInputState>> inputs_;

	// Constructor
	Input();

	// Destructor
	~Input() = default;

	// Reset all input values to the default state: kRelease
	void Reset();

	// Update
	void Update();

	// Get input state by its value
	EInputState get_input_state(EInputValue value) const;

	// Set the input value to desired state 
	void SetInputValue(EInputValue input, EInputState value);
	
	// Is the input value key pressed or not
	bool IsValueKeyPressed(EInputValue value) const { return inputs_[(size_t)value].second == Input::EInputState::kPress; }
	
	// Is the input value key just released or not
	bool IsValueKeyJustReleased(EInputValue value) const { return inputs_[(size_t)value].second == Input::EInputState::kJustRelease; }
};
