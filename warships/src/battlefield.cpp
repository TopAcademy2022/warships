#include "battlefield.h"

#include <cmath>
#include <random>
#include <vector>

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

bool battlefield::Battlefield::CanPlaceShip(const std::list<logic::Cell>& candidateCells) const
{
	for (const logic::Cell& newCell : candidateCells)
	{
		const int nx = static_cast<int>(newCell.GetPositionX());
		const int ny = static_cast<int>(newCell.GetPositionY());

		if (nx < 1 || nx > 10 || ny < 1 || ny > 10)
		{
			return false;
		}

		for (const logic::Ship& existingShip : this->_ships)
		{
			for (const logic::Cell& existingCell : existingShip.GetDecks())
			{
				const int ex = static_cast<int>(existingCell.GetPositionX());
				const int ey = static_cast<int>(existingCell.GetPositionY());

				if (std::abs(nx - ex) <= 1 && std::abs(ny - ey) <= 1)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool battlefield::Battlefield::TryGenerateShips(std::mt19937& rng)
{
	struct ShipSpec
	{
		logic::ShipTypes type;
		unsigned int deckCount;
	};

	const std::vector<ShipSpec> fleet = {
		{ logic::ShipTypes::FourDeck, 4 },
		{ logic::ShipTypes::TripleDeck, 3 },
		{ logic::ShipTypes::TripleDeck, 3 },
		{ logic::ShipTypes::DoubleDeck, 2 },
		{ logic::ShipTypes::DoubleDeck, 2 },
		{ logic::ShipTypes::DoubleDeck, 2 },
		{ logic::ShipTypes::SingleDeck, 1 },
		{ logic::ShipTypes::SingleDeck, 1 },
		{ logic::ShipTypes::SingleDeck, 1 },
		{ logic::ShipTypes::SingleDeck, 1 }
	};

	std::uniform_int_distribution<int> orientationDist(0, 1);
	const unsigned int MAX_ATTEMPTS_PER_SHIP = 150;

	for (const ShipSpec& spec : fleet)
	{
		bool shipPlaced = false;

		for (unsigned int attempt = 0; attempt < MAX_ATTEMPTS_PER_SHIP; ++attempt)
		{
			const bool isHorizontal = (orientationDist(rng) == 0);

			const unsigned int maxX = isHorizontal ? (10 - spec.deckCount + 1) : 10;
			const unsigned int maxY = isHorizontal ? 10 : (10 - spec.deckCount + 1);

			std::uniform_int_distribution<unsigned int> xDist(1, maxX);
			std::uniform_int_distribution<unsigned int> yDist(1, maxY);

			const unsigned int startX = xDist(rng);
			const unsigned int startY = yDist(rng);

			std::list<logic::Cell> candidateCells;
			for (unsigned int i = 0; i < spec.deckCount; ++i)
			{
				const unsigned int x = isHorizontal ? (startX + i) : startX;
				const unsigned int y = isHorizontal ? startY : (startY + i);
				candidateCells.emplace_back(x, y);
			}

			if (this->CanPlaceShip(candidateCells))
			{
				this->_ships.emplace_back(std::move(candidateCells), spec.type);
				shipPlaced = true;
				break;
			}
		}

		if (!shipPlaced)
		{
			return false;
		}
	}

	return true;
}

void battlefield::Battlefield::RebuildEmptyCells()
{
	this->_emptyCells.clear();
	for (unsigned int x = 1; x <= 10; ++x)
	{
		for (unsigned int y = 1; y <= 10; ++y)
		{
			logic::Cell cell(x, y);
			if (this->FindShipByCell(cell) == nullptr)
			{
				this->_emptyCells.push_back(cell);
			}
		}
	}
}

void battlefield::Battlefield::InitShipsAutomaticMode(std::mt19937& rng)
{
	const unsigned int MAX_RESTARTS = 500;

	for (unsigned int restart = 0; restart < MAX_RESTARTS; ++restart)
	{
		this->_ships.clear();
		if (this->TryGenerateShips(rng))
		{
			this->RebuildEmptyCells();
			return;
		}
	}

	this->RebuildEmptyCells();
}

battlefield::Battlefield::Battlefield(ShipDeploymentMode shipDeploymentMode)
{
	if (shipDeploymentMode == AutomaticMode)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		this->InitShipsAutomaticMode(rng);
	}
	else
	{
		this->RebuildEmptyCells();
		this->InitShipsManualMode();
	}
}

battlefield::Battlefield::Battlefield(ShipDeploymentMode shipDeploymentMode, unsigned int seed)
{
	if (shipDeploymentMode == AutomaticMode)
	{
		std::mt19937 rng(seed);
		this->InitShipsAutomaticMode(rng);
	}
	else
	{
		this->RebuildEmptyCells();
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