#pragma once

#include "ObjBase.h"

class Bomb: public ObjBase
{
	static const int kXSize = 13;
	static const int kYSize = 16;
	static const double kAnimationTime;

public:
	static vector<AnimationPair> animation_vec_;
	static const int kDamage;

	// Constructor & Destructor
	Bomb(ObjBase* player, EDirection faceDirection);
	~Bomb() = default;

	// Update 
	void Update() override;

	// Draw
	HBITMAP GethBmp() override;
	BITMAP GetBitmap() override;
};

