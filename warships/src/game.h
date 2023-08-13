#pragma once


#include <ctime>
#include "battlefield.h"

class Game
{
private:
	std::list<battlefield::Battlefield*> _battlefield;

	time_t _startTime;

public:
	Game(battlefield::ShipDeploymentMode firstPlayerInitShipsMode, battlefield::ShipDeploymentMode secondPlayerInitShipsMode);

	std::list<battlefield::Battlefield*> GetBattlefields();

	time_t GetLastTime();
};