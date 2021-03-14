#pragma once
#include <cmath>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair
#include "FrameTimer.h"
#include "MyMath.h"
using std::vector;
using std::pair;
typedef pair<HBITMAP, BITMAP> AnimationPair;

// The script is for providing basic functions for all game objects. 
class ObjBase
{
protected:
#pragma region Transform
	// The current x position of the object
	float x_;

	// The current y position of the object
	float y_;

	// The object's x size for rendering
	float x_size_;

	// The object's y size for rendering
	float y_size_;

	// The object's render rect
	MyRect rect_;
#pragma endregion Transform

public:
	// Constructor 
	ObjBase::ObjBase() : x_(0), y_(0), x_size_(0), y_size_(0), rect_() {}

	// Destructor
	virtual ~ObjBase() = default;

#pragma region Getters & Setters
	// Get x position of the object
	float get_x() const { return x_; }

	// Get y position of the object
	float get_y() const { return y_; }

	// Get x size of the object
	float get_x_size() const { return x_size_; }

	// Get y size of the object
	float get_y_size() const { return y_size_; }

	// Get the render rect of the object
	MyRect get_rect() const { return rect_; }
#pragma endregion Getters & Setters

	// Update
	virtual void Update() {};

#pragma region Render
	// Render the bitmap with a tranparent color
	void DrawTransparent(HDC& hdcScreen, HDC& hdcMemory, int transparent);

	// Render the bitmap completely
	void DrawAll(HDC& hdcScreen, HDC& hdcMemory);

	// Get the h-bitmap which should be displaying currently
	virtual HBITMAP GethBmp() { return HBITMAP(); }
	
	// Get the bitmap which should be displaying currently
	virtual BITMAP GetBitmap() { return BITMAP(); }
#pragma endregion Render

	// Load bitmap images to hBMP and bitmap
	static void LoadImages(HINSTANCE hInstance, vector<AnimationPair> & animationVec, int startIDB, int endIDB);
};

