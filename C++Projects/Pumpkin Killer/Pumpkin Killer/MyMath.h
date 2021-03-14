#pragma once

// The struct is for defining a rect which is used for gameobjects' rendering and collision
struct MyRect
{
public: 
	// The furthest side along the x-axis
	float right;

	// The furthest side along the y-axis
	float bottom;
	
	// The nearest side along the x-axis
	float left;
	
	// The nearest side along the y-axis
	float top;

	// Constructor
	MyRect() = default;

	// Constructor
	MyRect(float rightValue, float bottomValue, float leftValue, float topValue) : right(rightValue), left(leftValue), bottom(bottomValue), top(topValue) {}

	// Set the four values of the rect
	void set_rect(float rightValue, float bottomValue, float leftValue, float topValue) { right = rightValue; bottom = bottomValue; left = leftValue; top = topValue; }

	// Operator overloading for +
	MyRect operator+(const MyRect& rhs) { return MyRect{ right + rhs.right, bottom + rhs.bottom, left + rhs.left, top + rhs.top };}
};

// The enum class defines 4 directions 
enum class EDirection
{
	kUp,
	kDown,
	kRight,
	kLeft,
	kNull
};






