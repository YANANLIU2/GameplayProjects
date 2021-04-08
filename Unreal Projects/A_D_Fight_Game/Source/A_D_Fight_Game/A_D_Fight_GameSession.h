#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"

class A_D_Fight_GameSession :
    public AGameSession
{
public: 
    void HandleMatchHasStarted() override;
};

