#include <iostream>
#include <vector>
#include "DynamicArray.h"

class ObjBase;
class Game
{
private:
	// How many spike should be on screen now
	int spike_num_;

	// Whether the game playing or not
	bool is_playing_;

	// Player pointer
	ObjBase* player_;

	// An array of spikes
	DynamicArray<ObjBase*> spike_array_;

	// Bitmaps for the player and spikes
	HBITMAP h_player_bmp_;
	
	BITMAP player_bmp_;
	
	HBITMAP h_spike_bmp_;
	
	BITMAP spike_bmp_;
	
	HBITMAP h_background_bmp_;

	BITMAP background_bmp_;

	// The window handle
	HWND h_window_;

	// Disable the three function for the singleton pattern
	Game(const Game& game) = delete;
	
	// Constructor
	Game()
		: is_playing_(true)
		, spike_num_(4)
		, player_(nullptr)
		, h_player_bmp_()
		, player_bmp_()
		, h_spike_bmp_()
		, spike_bmp_()
		, h_window_()
		, h_background_bmp_()
		, background_bmp_()
		, spike_array_(spike_num_, nullptr)
	{
	}
	
	// Distructor
	~Game();

public:
	// Singleton
	static Game& Get()
	{
		static Game instance;
		return instance;
	}

	// Initialization
	bool Init(HWND hWindow, HINSTANCE hInstance);

	// Update
	void Update();

	// Draw
	void Draw();

	// Destroy all gameobjects 
	void Cleanup();

	// Reset
	void Reset();

	// Player movement
	void Movement(bool right);

	// Calculate all gameobjects' collision
	void Collision();

	// Whether one object collides with another object or not 
	bool CollideWith(ObjBase* objectOne, ObjBase* objectTwo);

	// Getters & Getters
	bool get_is_playing() const { return is_playing_; }

	void set_is_playing(bool value) { is_playing_ = value; }
};

