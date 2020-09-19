#pragma once
#include <vector>
#include <memory>
#include <string>
#include <raylib.h>
#include "../lib/typedef.hh"
#include "CellWorld.hh"
struct CellWorld;

class Cell
{

public:
	std::string cellType = "Cell";
	float density = 0;
	struct
	{
		unsigned char valid : 1;
		unsigned char updated : 1;
		unsigned char frozen : 1;
		unsigned char changed : 1;
		unsigned char loose : 1;
		unsigned char F : 1;
		unsigned char G : 1;
		unsigned char H : 1;
	} gFlags{1, 0, 0, 0, 1, 0, 0, 0};
	Cell(CellWorld &p_world,
			 u32 x = 0,
			 u32 y = 0);
	~Cell();
	virtual void Update();
	virtual Color Draw();

	bool CheckAllNeighborsSolid();

	u32 x;
	u32 y;

protected:
	CellWorld &world;
};
