#include "cell.h"

logic::Cell::Cell(unsigned int positionX, unsigned int positionY)
{
	this->_positionX = positionX;
	this->_positionY = positionY;
	this->_isHit = false;
}

unsigned int logic::Cell::GetPositionX() const
{
	return this->_positionX;
}

unsigned int logic::Cell::GetPositionY() const
{
	return this->_positionY;
}

bool logic::Cell::GetIsHit() const
{
	return this->_isHit;
}

void logic::Cell::TakeHit()
{
	this->_isHit = true;
}
