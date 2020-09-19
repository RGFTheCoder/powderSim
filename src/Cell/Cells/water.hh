#pragma once
#include "../Cell.hh"
#include "../../random.hh"

class Water : public Cell
{
public:
	float density = 50;

	using Cell::Cell;

	void Update()
	{

		if (CheckAllNeighborsSolid())
		{
			gFlags.frozen = true;
		}

		WithRetCode<Cell *> ret = world.swap(x, y, nullptr);
		if (ret.success)
		{
			Cell *me = ret.value;
			{
				using namespace RandomChoice;
				StartChoice()
						// ->Try(
						// 		)
						->Try({
								//
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 0, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 1, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x - 1, y - 1, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x + 1, y + 0, me); },
								[&]() -> bool { gFlags.frozen = false; return world.pos(x - 1, y + 0, me); }
								//
						})
						->Finally(
								[&]() -> bool { return world.pos(x, y, me); });
			}
		}
	};
	Color Draw()
	{
		if (gFlags.frozen)
			return {0xff, 0x00, 0x00, 0xff};
		return {35, 137, 218, 0xFF};
	};
};