#pragma once
#include "Input.h"

class Player;

class Command
{
public:
	enum class ECommandType
	{
		kNone,
		kMove,
		kAttack,
		kActionNums
	};

protected:
	ECommandType commandType_;
	Player* player_;
	
public:
	Command(Player* pPlayer) : player_(pPlayer), commandType_(ECommandType::kNone){}

	virtual ~Command() {}

	virtual void Execute(); 

	Command::ECommandType GetType() { return commandType_; }
};


