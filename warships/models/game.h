#pragma once


#include <list>
#include "battlefield.h"

class Game
{
private:
	std::list<Battlefield*> _battlefield;

	unsigned int _lastTime;

public:
	Game(std::list<Battlefield*> battlefield, unsigned int lastTime);

	std::list<Battlefield*> GetBattlefield();

	unsigned int GetLastTime();
};