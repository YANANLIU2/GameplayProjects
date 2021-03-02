#pragma once
#include "ObjBase.h"

// The script is for providing basic functions for game objects which are expected to move and run animations
class Actor:
    public ObjBase
{
protected:
#pragma region Movement
	// The upper limit of the actor's speed
	float max_speed_;

	// The acclerarion of the actor for both x axis and y axis
	float acceleration_;

	// The current moving speed of the actor along x axis
	float x_speed_;

	// The current moving speed of the actor along y axis
	float y_speed_;
#pragma endregion Movement
	
	// Is the actor considered to be alive or active?
	bool is_alive_;

	// The actor's collision rect
	MyRect hitbox_;

	// The object's hitbox is smaller than its image size in all four directions. hitbox_offset_ decides the amount. 
	MyRect hitbox_offset_;

	// Timer for updating animation index
	FrameTimer animation_timer_;

	// The current animation index decides which sprite in the animation vector will be rendered
	size_t animation_index_;

	// The direction the actor should head to for this frame
	EDirection direction_;

	// Update render rect and collision rect based on position, size and hitbot_offset
	void UpdateRect();

public:
	// Construtor 
	Actor() : ObjBase(), max_speed_(3), acceleration_(0), x_speed_(0), y_speed_(0), hitbox_(), hitbox_offset_(), animation_timer_(0), animation_index_(0), is_alive_(true), direction_() {}
	
	// Destructor
	virtual ~Actor() = default;

#pragma region Getters & Setters
	// Get if the actor is alive
	bool get_is_alive() const { return is_alive_; }
	
	// Get the hitbox of the actor to calcualte collision 
	MyRect get_hitbox() const { return hitbox_; }
	
	// Set it to false to kill the actor
	void set_is_alive(bool alive) { is_alive_ = alive; }
#pragma endregion Getters & Setters

	// To make the actor not moving
	void StopMoving();

	// Update the animation timer, if it's finished play next sprite and reset the timer
	void UpdateAnimationIndex(size_t max, bool isLoop = true);
	
	// If the actor out ot screen, if it's allowed to do so just leave it there otherwise put it back to screen
	bool IsOutOfScreen(bool isAllowed = true);
	
	// Move the actor based on it's speed and current direction
	void Move();
	
	// Whether if the actor collide with another one or not
	bool IsCollidedWith(Actor* another);
};

