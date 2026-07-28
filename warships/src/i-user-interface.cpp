#include "i-user-interface.h"

IUserInterface::IUserInterface(IDatabase& iDatabase)
	: _controller(iDatabase)
{
}

Controller& IUserInterface::GetController()
{
	return this->_controller;
}
