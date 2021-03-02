#include "stdafx.h"
#include "MoveCommand.h"

MoveCommand::MoveCommand(Player * pObj, Input::InputValue direction)
	: Command(pObj)
{
	moveDirection_ = direction;
	commandType_ = Command::ECommandType::kMove;
}
