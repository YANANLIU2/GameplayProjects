#pragma once

#include "ObjBase.h"
#include "GameSettings.h"
class Player : public ObjBase
{
	const int kXSize = 30;
	const int kYSize = 75;
	const double kAnimationTime = 0.011;

	// Command
	vector<Command*> commands_vec;
	EDirection last_direction_;
public:
	static vector<AnimationPair> animation_vec_;

	// Constructor & Destructor
	Player();
	~Player();

	// Update
	void Update() override final;
	void HandleInput(Command* pCommand);

	// Draw
	HBITMAP GethBmp() override final;
	BITMAP GetBitmap() override final;

	// Command
	void AddCommand(Command* newCommand) { commands_vec.push_back(newCommand); }
};

