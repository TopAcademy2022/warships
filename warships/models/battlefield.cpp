#include "battlefield.h"

Battlefield::Battlefield(std::list<Ship*> ships, unsigned int countShips)
{
	this->_ships = ships;
	this->_countShips = countShips;
}

std::list<Ship*> Battlefield::GetShips()
{
	return this->_ships;
}

unsigned int Battlefield::GetCountShips()
{
	return this->_countShips;
}