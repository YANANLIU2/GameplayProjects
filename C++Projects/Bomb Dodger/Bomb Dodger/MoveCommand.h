#pragma once
#include "Command.h"

class MoveCommand :public Command
{
	Input::InputValue moveDirection_;

public:
	MoveCommand(Player* pObj, Input::InputValue direction);
	~MoveCommand() {};
	Input::InputValue GetDirection() { return moveDirection_; }
};
