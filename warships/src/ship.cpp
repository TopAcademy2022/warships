#include "ship.h"

#include <algorithm>
#include <utility>

logic::Ship::Ship(std::list<logic::Cell> cells, ShipTypes shipType)
	: _decks(std::move(cells)), _shipType(shipType)
{
}

logic::ShipTypes logic::Ship::GetShipType() const
{
	return this->_shipType;
}

bool logic::Ship::ContainsCell(const logic::Cell& cell) const
{
	return std::find_if(this->_decks.begin(), this->_decks.end(),
		[&cell](const logic::Cell& deck)
		{
			return deck.GetPositionX() == cell.GetPositionX() &&
				deck.GetPositionY() == cell.GetPositionY();
		}) != this->_decks.end();
}

std::list<logic::Cell>& logic::Ship::GetDecks()
{
	return this->_decks;
}

const std::list<logic::Cell>& logic::Ship::GetDecks() const
{
	return this->_decks;
}
