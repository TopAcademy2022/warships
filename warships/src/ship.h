#pragma once


#include <list>
#include "deck.h"

namespace ship
{
	enum ShipTypes
	{
		SingleDeck = 1,
		DoubleDeck = 2,
		TripleDeck = 3,
		FourDeck = 4
	};

	class Ship
	{
	private:
		std::list<Deck*> _decks;

		ShipTypes _shipType;

	public:
		Ship(std::list<Deck*> decks, ShipTypes shipType);

		std::list<Deck*> GetDecks();

		ShipTypes GetShipType();
	};
}