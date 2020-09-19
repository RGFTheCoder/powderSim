#pragma once
#include "../lib/typedef.hh"
#include "Cell.hh"
#include <vector>
class Cell;

struct Position
{
	u32 x;
	u32 y;
};

class CellWorld
{
protected:
	std::vector<Cell *> zaWarudo;
	u32 w;
	u32 h;

public:
	std::vector<Position> changes;

public:
	CellWorld();
	CellWorld(u32 p_w, u32 p_h);

	//Updates the world.
	void UpdateWorld();

	//Returns true if emptied, false if already empty.
	inline bool empty(u32 x, u32 y)
	{
		if (x < 0 || x >= w)
			return false;
		if (y < 0 || y >= h)
			return false;

		if (zaWarudo[y * w + x] == nullptr)
		{
			return false;
		}
		else
		{
			zaWarudo[y * w + x] = nullptr;
			changes.push_back({x, y});
			return true;
		}
	};

	void unfreezeNeighbors(u32 x, u32 y);
	void updateCell(Cell *cell, u32 x, u32 y);

	//Place cell at position if empty (returns success)
	bool pos(u32 x, u32 y, Cell *cell);

	//Get cell at position
	inline WithRetCode<Cell *> pos(u32 x, u32 y) const
	{
		if (x < 0 || x >= w)
			return {nullptr, false};
		if (y < 0 || y >= h)
			return {nullptr, false};

		return {zaWarudo[y * w + x], true};
	};

	//Replaces the stored Cell with {cell} and returns a pointer to the stored Cell.
	WithRetCode<Cell *> swap(u32 x, u32 y, Cell *cell);
};