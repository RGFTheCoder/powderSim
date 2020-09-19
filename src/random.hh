#pragma once
#include <random>
#include <functional>
#include <algorithm>
#include <vector>
#include "lib/typedef.hh"
#include "Cell/CellWorld.hh"

std::random_device rd;	//Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> dis(0.0, 1.0);
auto randomFrac = std::bind(dis, gen);

// void a()
// {
// 	using namespace RandomChoice;
// 	CellWorld world;
// 	int x, y;
// 	Cell *me;
// 	StartChoice()
// 			->Try(
// 					[&]() -> bool { return world.pos(x, y - 1, me); })
// 			->Try(
// 					[&]() -> bool { return world.pos(x + 1, y - 1, me); },
// 					[&]() -> bool { return world.pos(x - 1, y - 1, me); },
// 					[&]() -> bool { return world.pos(x + 1, y + 0, me); },
// 					[&]() -> bool { return world.pos(x - 1, y + 0, me); })
// 			->Finally(
// 					[&]() -> bool { return world.pos(x, y, me); });
// }

namespace RandomChoice
{
	inline u32 perms(u32 len)
	{
		return ((len + 1) * len) >> 1;
	}

	struct _Choice
	{
		using BoolFunc = std::function<bool()>;
		bool done = false;
		inline _Choice *Try(BoolFunc f1)
		{
			if (done)
				return this;
			done = f1();
			return this;
		}
		inline void Finally(BoolFunc f1)
		{
			if (!done)
				f1();
			delete this;
		}
		inline _Choice *Try(BoolFunc f1, BoolFunc f2)
		{
			if (done)
				return this;

			bool chosen = randomFrac() < 0.5;
			if (chosen)
				done = f1();
			else
				done = f2();

			if (done)
				return this;

			if (chosen)
				done = f2();
			else
				done = f1();
			return this;
		}
		inline _Choice *Try(std::vector<BoolFunc> funcs)
		{
			if (done)
				return this;

			std::shuffle(funcs.begin(), funcs.end(), gen);

			while (funcs.size() > 0)
			{
				done = funcs.at(funcs.size() - 1)();
				funcs.pop_back();
				if (done)
					return this;
			}

			return this;
		}
	};

	_Choice *StartChoice()
	{
		return new _Choice();
	}

} // namespace RandomChoice
