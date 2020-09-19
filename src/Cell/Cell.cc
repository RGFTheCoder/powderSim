#include "Cell.hh"

Cell::Cell(CellWorld &p_world,
					 u32 x,
					 u32 y)
		: world(p_world)
{
	gFlags.valid = world.pos(x, y, this);
	// delete this;
};

Cell::~Cell() {}

void Cell::Update(){

};
Color Cell::Draw()
{
	return {0xff, 0xff, 0xff, 0xff};
};

bool Cell::CheckAllNeighborsSolid()
{
	return ((world.pos(x - 1, y - 1).value != nullptr) && (world.pos(x + 0, y - 1).value != nullptr) && (world.pos(x + 1, y - 1).value != nullptr)) &&
				 ((world.pos(x - 1, y + 0).value != nullptr) && (/*             */ true /*             */) && (world.pos(x + 1, y + 0).value != nullptr)) &&
				 ((world.pos(x - 1, y + 1).value != nullptr) && (world.pos(x + 0, y + 1).value != nullptr) && (world.pos(x + 1, y + 1).value != nullptr));
}