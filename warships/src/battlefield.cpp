#include "battlefield.h"

logic::Ship* battlefield::Battlefield::FindShipByCell(const logic::Cell& cell)
{
	for (logic::Ship& currentShip : this->_ships)
	{
		if (currentShip.ContainsCell(cell))
		{
			return &currentShip;
		}
	}

	return nullptr;
}

std::list<logic::Cell> battlefield::Battlefield::TakeEmptyCells(unsigned int count)
{
	std::list<logic::Cell> cells;

	while (count > 0 && !this->_emptyCells.empty())
	{
		cells.splice(cells.end(), this->_emptyCells, this->_emptyCells.begin());
		--count;
	}

	return cells;
}

void battlefield::Battlefield::InitShipsManualMode()
{
	// Manual ship deployment will use the same cells collection when implemented.
}

void battlefield::Battlefield::InitShipsAutomaticMode()
{
	this->_ships.emplace_back(this->TakeEmptyCells(logic::ShipTypes::FourDeck),
		logic::ShipTypes::FourDeck);

	const unsigned int COUNT_SHIPS_TRIPLE_DECK = 2;
	for (unsigned int i = 0; i < COUNT_SHIPS_TRIPLE_DECK; ++i)
	{
		this->_ships.emplace_back(this->TakeEmptyCells(logic::ShipTypes::TripleDeck),
			logic::ShipTypes::TripleDeck);
	}

	const unsigned int COUNT_SHIPS_DOUBLE_DECK = 3;
	for (unsigned int i = 0; i < COUNT_SHIPS_DOUBLE_DECK; ++i)
	{
		this->_ships.emplace_back(this->TakeEmptyCells(logic::ShipTypes::DoubleDeck),
			logic::ShipTypes::DoubleDeck);
	}

	const unsigned int COUNT_SHIPS_SINGLE_DECK = 4;
	for (unsigned int i = 0; i < COUNT_SHIPS_SINGLE_DECK; ++i)
	{
		this->_ships.emplace_back(this->TakeEmptyCells(logic::ShipTypes::SingleDeck),
			logic::ShipTypes::SingleDeck);
	}
}

battlefield::Battlefield::Battlefield(ShipDeploymentMode shipDeploymentMode)
{
	for (unsigned int x = 1; x <= 10; ++x)
	{
		for (unsigned int y = 1; y <= 10; ++y)
		{
			this->_emptyCells.emplace_back(x, y);
		}
	}

	if (shipDeploymentMode == AutomaticMode)
	{
		this->InitShipsAutomaticMode();
	}
	else
	{
		this->InitShipsManualMode();
	}
}

std::list<logic::Ship>& battlefield::Battlefield::GetShips()
{
	return this->_ships;
}

const std::list<logic::Ship>& battlefield::Battlefield::GetShips() const
{
	return this->_ships;
}
