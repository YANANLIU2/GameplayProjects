#pragma once
#include "StateMachine.h"

struct PlayerData;
class PlayerStateMachine : StateMachine
{
public:
	PlayerStateMachine() : StateMachine(ST_MAX_STATES){}

	// External events taken by this tate machine
	void Attack();
	void Defend();
	void Counter();
	void Evade();
	void Block();

private:
	// State macchine state functions
	void ST_Idle(PlayerData*);
	void ST_Attack(PlayerData*);
	void ST_Defend(PlayerData*);
	void ST_Counter(PlayerData*);
	void ST_Evade(PlayerData*);
	void ST_Block(PlayerData*);

	// State map to define state function order 
	BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Idle)
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Attack)
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Defend)
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Counter)
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Evade)
		STATE_MAP_ENTRY(&PlayerStateMachine::ST_Block)
	END_STATE_MAP

	// State enumeration order must match the order of state method entries in the state map
	enum E_States
	{
		ST_IDLE,
		ST_ATTACK,
		ST_DEFEND,
		ST_COUNTER,
		ST_EVADE,
		ST_BLOCK,

		ST_MAX_STATES
	};
};