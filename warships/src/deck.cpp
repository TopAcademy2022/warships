#include "deck.h"

Deck::Deck(unsigned int positionX, unsigned int positionY, bool isAlive)
{
	this->_positionX = positionX;
	this->_positionY = positionY;
	this->_isAlive = isAlive;
}

unsigned int Deck::GetPositionX()
{
	return this->_positionX;
}

unsigned int Deck::GetPositionY()
{
	return this->_positionY;
}

bool Deck::GetIsAlive()
{
	return this->_isAlive;
}