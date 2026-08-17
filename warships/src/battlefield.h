#pragma once

#include <list>
#include <random>
#include <vector>

#include "ship.h"
#include "cell.h"

namespace battlefield
{
	enum ShipDeploymentMode
	{
		ManualMode = 0,
		AutomaticMode = 1
	};

	class Battlefield
	{
	private:
		std::list<logic::Cell> _emptyCells;

		std::list<logic::Ship> _ships;

		logic::Ship* FindShipByCell(const logic::Cell& cell);

		std::list<logic::Cell> TakeEmptyCells(unsigned int count);

		void InitShipsManualMode();

		void InitShipsAutomaticMode(std::mt19937& rng);

		bool CanPlaceShip(const std::list<logic::Cell>& candidateCells) const;

		bool TryGenerateShips(std::mt19937& rng);

		void RebuildEmptyCells();

	public:
		explicit Battlefield(ShipDeploymentMode shipDeploymentMode = AutomaticMode);

		Battlefield(ShipDeploymentMode shipDeploymentMode, unsigned int seed);

		std::list<logic::Ship>& GetShips();

		const std::list<logic::Ship>& GetShips() const;
	};
}