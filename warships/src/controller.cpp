#include "controller.h"

Controller::Controller(IDatabase* iDatabase)
{
	this->_iDatabase = iDatabase;
	this->_game = nullptr;
}

void Controller::InitGame(Game* game)
{
	this->_game = game;
}

IDatabase* Controller::GetIDatabase()
{
	return this->_iDatabase;
}

Game* Controller::GetGame()
{
	return this->_game;
}
