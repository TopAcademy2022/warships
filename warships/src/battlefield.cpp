#include "battlefield.h"

void battlefield::Battlefield::InitShipsManualMode()
{

}

void battlefield::Battlefield::InitShipsAutomaticMode()
{

}

battlefield::Battlefield::Battlefield(ShipDeploymentMode shipDeploymentMode)
{
	if (shipDeploymentMode == ShipDeploymentMode::AutomaticMode)
	{
		this->InitShipsAutomaticMode();
	}
	else
	{
		this->InitShipsManualMode();
	}
}

std::list<ship::Ship*> battlefield::Battlefield::GetShips()
{
	return this->_ships;
}