#pragma once
// UE4 
#include "Engine.h"

DECLARE_EVENT(FLayerViewModel, FPowerUpEvent)
class PowerUpBroadcaster
{
private:
	FPowerUpEvent PowerUpEventInstance;

public:
	static PowerUpBroadcaster& GetInstance()
	{
		static PowerUpBroadcaster Instance;
		return Instance;
	}

	FPowerUpEvent& OnPowerUpActivated() { return PowerUpEventInstance; }

	void BroadPowerUpActivated();
	
private: 
	PowerUpBroadcaster() = default;

	~PowerUpBroadcaster() = default;

	PowerUpBroadcaster(const PowerUpBroadcaster&) = delete;

	PowerUpBroadcaster& operator = (const PowerUpBroadcaster&) = delete;
};

