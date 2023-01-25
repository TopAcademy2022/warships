#pragma once
#include <list>
#include "battlefield.h"

class Game
{
	std::list<Battlefield*> _battlefield;

	unsigned int _lastTime;
};