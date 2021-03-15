#include "ObjBase.h"

class Spike: public ObjBase
{
public:
	// Constructor
	Spike();

	// Destructor
	~Spike() = default;

	// Reset
	void Reset() override;

	// If the player is vertically outside of the screen => put it back to the top of the screen
	void OutofBox() override;
};

