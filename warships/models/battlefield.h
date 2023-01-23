#pragma once
#include <list>
#include "ship.h"

class Battlefield
{
	std::list<Ship*> _ships;

	unsigned int _countShips;
};