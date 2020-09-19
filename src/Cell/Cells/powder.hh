#pragma once
#include "../Cell.hh"
#include "../../random.hh"

class Powder : public Cell
{
public:
	float density = 100;

	using Cell::Cell;

	void Update()
	{
		WithRetCode<Cell *> ret = world.swap(x, y, nullptr);
		if (ret.success)
		{
			Cell *me = ret.value;
			bool random1 = randomFrac() < 0.5;
			// bool random2 = randomFrac() < 0.5;

			world.pos(x, y - 1, me) ||
					(random1 ? world.pos(x - 1, y - 1, me) : world.pos(x + 1, y - 1, me)) ||
					(random1 ? world.pos(x + 1, y - 1, me) : world.pos(x - 1, y - 1, me)) ||
					world.pos(x, y, me);
		}

		if (CheckAllNeighborsSolid())
		{
			gFlags.frozen = true;
			world.changes.push_back({x, y});
		}
	};
	Color Draw()
	{
		// if (frozen)
		// 	return {0xff, 0x00, 0x00, 0xff};
		return {0xF2, 0xD1, 0x6B, 0xFF};
	};
};