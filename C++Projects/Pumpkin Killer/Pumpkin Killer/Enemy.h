#pragma once
#include "Actor.h"

// The script is for updating and rendering the enemies
class Player;
class Enemy :
	public Actor
{
	const float kMaxSpeedAccelerationOverTime = 1.0001f;

	// The player pointer. An enemy needs the player's position for moving towards the player
	Player* player_;

	// It will decide which direction an enemy will walk towards for this frame
	void WalkToPlayer();

protected:
	// One enemy's health points. when it goes to 0 the enemy dies. 
	int health_points_;
	
public:
	// An array of animations for all enemies 
	static vector<AnimationPair> animation_vec_;

	// Construtor 
	Enemy(Player* player_, float x = 200, float y= 200);

	// Destructor
	~Enemy() = default;

	// Get the health point value of the enemy
	int get_health_points() const{ return health_points_; }

	// Set the health point value of the enemy
	void set_health_points(int value) { health_points_ = value; }

	// Update
	void Update() override final;

	// Render
	HBITMAP GethBmp() override final;

	BITMAP GetBitmap() override final;

	// Gameplay
	void GetHit(int dmg);
};

