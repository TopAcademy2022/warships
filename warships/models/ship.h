#pragma once


#include <list>
#include "deck.h"

class Ship
{
private:
	std::list<Deck*> _decks;

	unsigned int _shipSize;

public:
	Ship(std::list<Deck*> decks, unsigned int shipSize);

	std::list<Deck*> GetDecks();

	unsigned int GetShipSize();
};