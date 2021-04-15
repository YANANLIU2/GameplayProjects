#include "PowerUpBroadcaster.h"

void PowerUpBroadcaster::BroadPowerUpActivated()
{
	PowerUpEventInstance.Broadcast();
}
