#include "ObjBase.h"

class Player : public ObjBase
{
public:
	// Constructor
	Player();
	
	// Destructor
	~Player() = default;
	
	// Reset
	void Reset() override;

	// If the player is horizontally outside of the screen => put it back to the screen
	void OutofBox() override;

	// Update
	void Update() final override;
};

