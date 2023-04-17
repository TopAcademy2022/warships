#include "controller.h"

Controller::Controller(IDatabase* IDatabase, Game* game)
{
	this->_IDatabase = IDatabase;
	this->_game = game;
}

void Controller::StartGame()
{
	std::cout << "Start game." << std::endl;
}