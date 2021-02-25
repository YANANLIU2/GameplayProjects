#pragma once

struct MyRect
{
public: 
	float right;
	float bottom;
	float left;
	float top;

	MyRect()
		: right(0)
		, left(0)
		, bottom(0)
		, top(0)
	{

	}

	MyRect(float rightValue, float bottomValue, float leftValue, float topValue)
		: right(rightValue)
		, left(leftValue)
		, bottom(bottomValue)
		, top(topValue)
	{
	}

	void set_rect(float rightValue, float bottomValue, float leftValue, float topValue)
	{
		right = rightValue;
		bottom = bottomValue;
		left = leftValue;
		top = topValue;
	}
};

enum class EDirection
{
	kStop,
	kUp,
	kDown,
	kRight,
	kLeft,
};