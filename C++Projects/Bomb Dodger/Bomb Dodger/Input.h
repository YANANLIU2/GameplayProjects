#pragma once
class Command;
class Player;
class Input
{
private:
	Player * player_;
public:
	enum class InputValue
	{
		kNone,
		kMoveUp,
		kMoveDown,
		kMoveRight,
		kMoveLeft,
		kStopMove,
		kAttackUp,
		kAttackDown,
		kAttackLeft,
		kAttackRight,
		kQuit,
		kSkip,
		kInputsNum
	};

	Input(Player* pPlayer)
		: player_(pPlayer)
	{
	}
	Input() = default;
	~Input() = default;
	void set_player(Player* player) { player_ = player; }
	void HandleRawInput(InputValue inputvalue);
};
