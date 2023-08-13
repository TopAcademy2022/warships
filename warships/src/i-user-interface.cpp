#include "i-user-interface.h"

IUserInterface::IUserInterface(IDatabase* iDatabase)
{
	this->_controller = new Controller(iDatabase);
}

Controller* IUserInterface::GetController()
{
	return this->_controller;
}
