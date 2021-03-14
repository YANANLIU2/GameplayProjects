#pragma once
#include "Actor.h"

// The script is for updating and rendering the bombs the player fires. 
class Bomb: public Actor
{
	// The time interval for animation update
	static const double kAnimationTime;

public:
	// An array of animations for all bombs 
	static vector<AnimationPair> animation_vec_;

	// The damage one bomb hit can cause towards an enemy
	static const int kDamage;

	// Constructor 
	Bomb(float x, float y, EDirection dir);

	// Destructor
	~Bomb() = default;

	// Update 
	void Update() override;

	// Render
	HBITMAP GethBmp() override;

	BITMAP GetBitmap() override;
};

