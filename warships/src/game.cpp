#include "game.h"

Game::Game(battlefield::ShipDeploymentMode firstPlayerInitShipsMode, battlefield::ShipDeploymentMode secondPlayerInitShipsMode)
{
	battlefield::Battlefield* firstPlayerBattlefield = new battlefield::Battlefield(firstPlayerInitShipsMode);
	battlefield::Battlefield* secondPlayerBattlefield = new battlefield::Battlefield(secondPlayerInitShipsMode);

	this->_battlefield.push_back(firstPlayerBattlefield);
	this->_battlefield.push_back(secondPlayerBattlefield);

	this->_startTime = time(NULL);
}

std::list<battlefield::Battlefield*> Game::GetBattlefields()
{
	return std::list<battlefield::Battlefield*>();
}

time_t Game::GetLastTime()
{
	time_t currentTime = time(NULL);
	return currentTime - this->_startTime;
}