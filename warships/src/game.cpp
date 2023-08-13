#include "game.h"

Game::Game(battlefield::ShipDeploymentMode firstPlayerInitShipsMode,
	battlefield::ShipDeploymentMode secondPlayerInitShipsMode)
{
	this->_battlefields.emplace_back(firstPlayerInitShipsMode);
	this->_battlefields.emplace_back(secondPlayerInitShipsMode);

	this->_startTime = time(NULL);
}

std::list<battlefield::Battlefield>& Game::GetBattlefields()
{
	return this->_battlefields;
}

const std::list<battlefield::Battlefield>& Game::GetBattlefields() const
{
	return this->_battlefields;
}

time_t Game::GetLastTime() const
{
	time_t currentTime = time(NULL);
	return currentTime - this->_startTime;
}
