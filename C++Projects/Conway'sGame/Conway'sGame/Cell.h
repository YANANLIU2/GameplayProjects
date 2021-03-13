#pragma once
class Cell
{
	// The cell's current state
	bool is_alive_;

public:
	// Constructor
	Cell() : is_alive_(false) {}
	
	// Destructor
	~Cell() = default;

	// Setters & Getters
	inline void set_is_alive(bool value) { is_alive_ = value; }

	inline bool get_is_alive() const { return is_alive_; }

	inline void set_is_alive_toggle() { is_alive_ = !is_alive_; }

	// Update
	void Update(int neighborNum);
};
