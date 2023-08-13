#include "ship.h"

ship::Ship::Ship(std::list<Deck*> decks, ShipTypes shipType)
{
	this->_decks = decks;
	this->_shipType = shipType;
}

std::list<Deck*> ship::Ship::GetDecks()
{
	return this->_decks;
}

ship::ShipTypes ship::Ship::GetShipType()
{
	return this->_shipType;
}