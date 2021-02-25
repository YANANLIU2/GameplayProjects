#pragma once

#include <cmath>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair

#include "FrameTimer.h"
#include "Command.h"
#include "MyMath.h"

using std::vector;
using std::pair;

typedef pair<HBITMAP, BITMAP> AnimationPair;

class Bomb;
class ObjBase
{
protected:
	// Movement
	float max_speed_;
	float acc_rate_;
	float x_acceleration_;
	float y_acceleration_;
	float x_speed_;
	float y_speed_;

	// Transform
	float x_;
	float y_;
	int x_size_;
	int y_size_;
	MyRect rect_;

	// Timer
	FrameTimer timer_;

	// Animation
	size_t animation_index_;

	// Gameplay
	bool is_alive_;
	EDirection direction_;

protected:
	
	void UpdateRect();

public:
	// Constructor & Destructor
	ObjBase::ObjBase()
		: max_speed_(3)
		, acc_rate_(1)
		, x_acceleration_(0)
		, y_acceleration_(0)
		, x_speed_(0)
		, y_speed_(0)
		, x_(0)
		, y_(0)
		, x_size_(0)
		, y_size_(0)
		, rect_()
		, timer_(0)
		, animation_index_(0)
		, is_alive_(true)
		, direction_(EDirection::kStop)
	{
	}

	virtual ~ObjBase() = default;

	// Getters & Setters
	float get_x() const { return x_; }
	float get_y() const { return y_; }
	int get_x_size() const { return x_size_; }
	int get_y_size() const { return y_size_; }
	bool get_is_alive() const { return is_alive_; }
	MyRect get_rect() const { return rect_; }
	void set_is_alive(bool alive) { is_alive_ = alive; }

	// Update
	virtual void Update() {};
	virtual HBITMAP GethBmp() { return HBITMAP(); }
	virtual BITMAP GetBitmap() { return BITMAP(); }

	// Helper
	bool IsOutOfScreen(bool isAllowed = true);

	// 
	void Move();
	void StopMoving();

	//
	void DrawTransparent(HDC& hdcScreen, HDC& hdcMemory, int transparent);
	void DrawAll(HDC& hdcScreen, HDC& hdcMemory);

	void UpdateAnimationIndex(size_t max, bool isLoop = true);
};

