#include "game.h"

Game::Game(std::list<Battlefield*> battlefield, unsigned int lastTime)
{
	this->_battlefield = battlefield;
	this->_lastTime = lastTime;
}

std::list<Battlefield*> Game::GetBattlefield()
{
	return this->_battlefield;
}

unsigned int Game::GetLastTime()
{
	return this->_lastTime;
}