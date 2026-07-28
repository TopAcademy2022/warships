#pragma once


namespace logic
{
	class Cell
	{
	private:
		unsigned int _positionX;

		unsigned int _positionY;

		bool _isHit;

	public:
		Cell(unsigned int positionX, unsigned int positionY);

		unsigned int GetPositionX() const;

		unsigned int GetPositionY() const;

		bool GetIsHit() const;

		void TakeHit();
	};
}
