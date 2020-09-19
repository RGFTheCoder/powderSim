#include "CellWorld.hh"

CellWorld::CellWorld() : zaWarudo(79 * 39)
{
	w = 79;
	h = 39;
};
CellWorld::CellWorld(u32 p_w, u32 p_h) : zaWarudo(p_w * p_h)
{
	w = p_w;
	h = p_h;
};

void CellWorld::unfreezeNeighbors(u32 x, u32 y)
{
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (!(dy == 0 && dx == 0))
			{
				Cell *ret = pos(x + dx, y + dy).value;
				if (ret != nullptr)
					ret->gFlags.frozen = false;
			}
		}
	}
};

void CellWorld::updateCell(Cell *cell, u32 x, u32 y)
{
	if (cell != nullptr)
	{
		cell->x = x;
		cell->y = y;
	}
	unfreezeNeighbors(x, y);
};

void CellWorld::UpdateWorld()
{

	for (u32 x = 0; x < w; ++x)
	{
		for (u32 y = 0; y < h; ++y)
		{
			auto currPos = pos(x, y);
			if (currPos.success && currPos.value != nullptr && currPos.value->gFlags.updated)
			{
				currPos.value->gFlags.updated = false;
			}
		}
	}

	for (u32 x = 0; x < w; ++x)
	{
		for (u32 y = 0; y < h; ++y)
		{
			auto currPos = pos(x, y);
			if (currPos.success && currPos.value != nullptr && !currPos.value->gFlags.updated && !currPos.value->gFlags.frozen)
			{
				currPos.value->gFlags.updated = true;
				currPos.value->Update();
			}
		}
	}
}

//Place cell at position if empty (returns success)
bool CellWorld::pos(u32 x, u32 y, Cell *cell)
{
	if (zaWarudo[y * w + x] == nullptr)
	{
		zaWarudo[y * w + x] = cell;
		updateCell(cell, x, y);
		changes.push_back({x, y});
		return true;
	}
	else
	{
		return false;
	}
}

//Replaces the stored Cell with {cell} and returns a pointer to the stored Cell.
WithRetCode<Cell *> CellWorld::swap(u32 x, u32 y, Cell *cell)
{
	if (x < 0 || x >= w)
		return {nullptr, false};
	if (y < 0 || y >= h)
		return {nullptr, false};

	Cell *temp;
	temp = zaWarudo[y * w + x];
	updateCell(cell, x, y);
	changes.push_back({x, y});
	zaWarudo[y * w + x] = cell;
	return {temp, true};
}