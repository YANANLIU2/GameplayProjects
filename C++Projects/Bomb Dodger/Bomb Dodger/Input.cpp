#include "stdafx.h"
#include "Input.h"
#include "Command.h"
#include "Player.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#define Getsymbol m_pCharacterBase->Getsymbol()

void Input::HandleRawInput(InputValue inputvalue)
{
	Command* pCommand;
	switch (inputvalue)
	{
	case InputValue::kMoveDown:
	case InputValue::kMoveLeft:
	case InputValue::kMoveRight:
	case InputValue::kMoveUp:
	case InputValue::kStopMove:
		pCommand = new MoveCommand(player_, inputvalue);
		pCommand->Execute();
		player_->AddCommand(pCommand);
		break;
	case InputValue::kAttackDown:
	case InputValue::kAttackLeft:
	case InputValue::kAttackRight:
	case InputValue::kAttackUp:
		pCommand = new AttackCommand(player_, inputvalue);
		pCommand->Execute();
		player_->AddCommand(pCommand);
		break;
	default:
		break;
	}
}

