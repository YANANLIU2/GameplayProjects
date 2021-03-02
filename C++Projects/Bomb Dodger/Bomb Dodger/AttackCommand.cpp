#include "stdafx.h"
#include "AttackCommand.h"

AttackCommand::AttackCommand(Player* pObj, Input::InputValue attackType)
	: Command(pObj)
	,attackType_(attackType)
{
	commandType_ = Command::ECommandType::kAttack;
}

AttackCommand::~AttackCommand()
{
}
