#include "stdafx.h"
#include "GameState.h"
#include "ObjBase.h"

bool GameState::IsCollidedWith(ObjBase * ObjOne, ObjBase * ObjTwo)
{
	bool isRight = (ObjOne->get_rect().right < ObjTwo->get_rect().left);
	bool isLeft = (ObjOne->get_rect().left > ObjTwo->get_rect().right);
	bool isAbove = (ObjOne->get_rect().top > ObjTwo->get_rect().bottom);
	bool isBelow = (ObjOne->get_rect().bottom < ObjTwo->get_rect().top);
	bool isNotOverlapping = (isRight || isLeft || isAbove || isBelow);
	return !isNotOverlapping;
}

