#pragma once


#include <list>
#include "ship.h"

class Battlefield
{
private:
	std::list<Ship*> _ships;

	unsigned int _countShips;

public:
	Battlefield(std::list<Ship*> ships, unsigned int countShips);

	std::list<Ship*> GetShips();

	unsigned int GetCountShips();
};