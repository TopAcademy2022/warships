#pragma once


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

		void InitShipsAutomaticMode();

	public:
		explicit Battlefield(ShipDeploymentMode shipDeploymentMode = AutomaticMode);

		std::list<logic::Ship>& GetShips();

		const std::list<logic::Ship>& GetShips() const;
	};
}
