#pragma once


#include "ship.h"

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
		std::list<ship::Ship*> _ships;

		void InitShipsManualMode();

		void InitShipsAutomaticMode();

	public:
		Battlefield(ShipDeploymentMode shipDeploymentMode);

		std::list<ship::Ship*> GetShips();
	};
}