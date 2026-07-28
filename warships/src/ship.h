#pragma once


#include <list>
#include "cell.h"

namespace logic
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
		std::list<logic::Cell> _decks;

		ShipTypes _shipType;

	public:
		Ship(std::list<logic::Cell> cells, ShipTypes shipType);

		ShipTypes GetShipType() const;

		bool ContainsCell(const logic::Cell& cell) const;

		std::list<logic::Cell>& GetDecks();

		const std::list<logic::Cell>& GetDecks() const;
	};
}
