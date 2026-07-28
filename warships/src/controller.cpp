#include "controller.h"

#include <utility>

Controller::Controller(IDatabase& iDatabase)
	: _iDatabase(iDatabase), _game(nullptr)
{
}

void Controller::InitGame(std::unique_ptr<Game> game)
{
	this->_game = std::move(game);
}

IDatabase& Controller::GetIDatabase()
{
	return this->_iDatabase;
}

Game* Controller::GetGame()
{
	return this->_game.get();
}
