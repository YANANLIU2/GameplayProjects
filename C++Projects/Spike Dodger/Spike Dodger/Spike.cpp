#include "stdafx.h"
#include "Spike.h"

Spike::Spike()
{
	size_ = { 32, 32 };
	Reset();
}

void Spike::Reset()
{
	float value = float(rand() % 8 * 100);
	pos_ = { value , 0 };
	speed_ = { 0, (float)(1 * (rand() % 100) / 100.f + 0.7) };
}

void Spike::OutofBox()
{
	if (get_is_outside_bottom())
	{
		Reset();
	}
}
