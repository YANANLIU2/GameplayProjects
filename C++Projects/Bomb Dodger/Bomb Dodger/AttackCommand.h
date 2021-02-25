#pragma once
#include "Command.h"
class AttackCommand :
	public Command
{
	Input::InputValue attackType_;

public:
	AttackCommand(Player* pObj, Input::InputValue attackType);
	~AttackCommand();
};

