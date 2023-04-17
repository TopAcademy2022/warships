#include "ship.h"

Ship::Ship(std::list<Deck*> decks, unsigned int shipSize)
{
	this->_decks = decks;
	this->_shipSize = shipSize;
}

std::list<Deck*> Ship::GetDecks()
{
	return this->_decks;
}

unsigned int Ship::GetShipSize()
{
	return this->_shipSize;
}