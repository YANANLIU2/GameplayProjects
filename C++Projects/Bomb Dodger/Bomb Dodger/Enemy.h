#pragma once
#include "ObjBase.h"
#include <memory>
class Player;
class Enemy :
	public ObjBase
{
	// constants
	const int kXSize = 66;
	const int kYSize = 77;
	const int kMaxHp = 5;
	const double kAnimationTime = 0.011;

	std::shared_ptr<Player> player_;

	void WalkToPlayer();

protected:
	int hp_;
	
public:
	static vector<AnimationPair> animation_vec_;

	// Construtor & Destructor
	Enemy(std::shared_ptr<Player> player_, float x = 200, float y= 200);
	~Enemy() = default;

	// Getters & Setters
	int get_hp() const{ return hp_; }
	void set_hp(int value) { hp_ = value; }
	
	// Update
	void Update() override final;

	// Draw
	HBITMAP GethBmp() override final;
	BITMAP GetBitmap() override final;

	// Gameplay
	void GetHit(int dmg);
};

