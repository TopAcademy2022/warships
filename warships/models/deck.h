#pragma once


class Deck
{
private:
	unsigned int _positionX;

	unsigned int _positionY;

	bool _isAlive;

public:
	Deck(unsigned int positionX, unsigned int positionY, bool isAlive);

	unsigned int GetPositionX();

	unsigned int GetPositionY();

	bool GetIsAlive();
};