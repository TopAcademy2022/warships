#pragma once


#include <ctime>
#include "battlefield.h"

class Game
{
private:
	std::list<battlefield::Battlefield> _battlefields;

	time_t _startTime;

public:
	Game(battlefield::ShipDeploymentMode firstPlayerInitShipsMode = battlefield::AutomaticMode,
		battlefield::ShipDeploymentMode secondPlayerInitShipsMode = battlefield::AutomaticMode);

	std::list<battlefield::Battlefield>& GetBattlefields();

	const std::list<battlefield::Battlefield>& GetBattlefields() const;

	time_t GetLastTime() const;
};
