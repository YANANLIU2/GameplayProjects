#include <Windows.h>
#include "stdafx.h"
#include "Cell.h"
#include "GameSettings.h"

// Conway's game rules
// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by overpopulation.
// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
void Cell::Update(int neighborNum)
{
	if (is_alive_)
	{
		if (neighborNum < 2 || neighborNum > 3)
		{
			is_alive_ = false;
		}
	}
	else
	{
		if (neighborNum == 3)
		{
			is_alive_ = true;
		}
	}
}