#include "stdafx.h"
#ifndef OBJBASE_H
#define OBJBASE_H
#include "GameSettings.h"


#include "MyVector2.h"

class ObjBase
{
protected:
	// Position of the object 
	MyVector2<float> pos_;
	
	// The object's current moving speed
	MyVector2<float> speed_;
	
	// The object's size
	MyVector2<float> size_;

public:
	// Constructor
	ObjBase()
		: pos_(0, 0)
		, speed_(0, 0)
		, size_(0, 0)
	{
	}

	// Destructor
	virtual ~ObjBase() = default;

	// Draw
	void Draw(HDC& hdc, HDC& hdcMemory, HBITMAP hBmp, BITMAP bmp);

	// Reset the gameobject 
	virtual void Reset() = 0;

	// Movement
	void Move(MyVector2<float> dir);

	// Update
	virtual void Update();

	// If the gameobject is outside of the screen what to do
	virtual void OutofBox() = 0;

	// Getters & Setters
	bool get_is_outside_right() { return pos_.x_ > GAME_WIDTH - size_.x_; }

	bool get_is_outside_left() { return pos_.x_ < 0; }

	bool get_is_outside_bottom() { return pos_.y_ > GAME_HEIGHT; }

	MyVector2<float> get_size() { return size_; }

	MyVector2<float> get_pos() { return pos_; }
};



#endif // !OBJBASE_H

