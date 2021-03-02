#include "stdafx.h"
#include "Command.h"
#include "Player.h"

void Command::Execute()
{
	player_->HandleInput(this);
}


