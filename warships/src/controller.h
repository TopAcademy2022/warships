#pragma once

#include <memory>

#include "i-database.h"
#include "game.h"

class Controller
{
private:
	IDatabase& _iDatabase;

	std::unique_ptr<Game> _game;

public:
	explicit Controller(IDatabase& iDatabase);

	void InitGame(std::unique_ptr<Game> game);

	IDatabase& GetIDatabase();

	Game* GetGame();
};
