#pragma once
#include <list>
#include "deck.h"

class Ship
{
private:
	std::list<Deck*> _decks;

	unsigned int _shipSize;
};