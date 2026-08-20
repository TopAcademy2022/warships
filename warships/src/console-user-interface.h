#pragma once

#include <iostream>
#include "i-user-interface.h"
#include "game.h"

class ConsoleUserInterface : public IUserInterface
{
private:
	void CreateNewGame() override;
	void PrintGameBattleField() override;
	void LoadGame() override;
	void CreateNetworkGame() override;
	void SetSettings() override;
	void Exit() override;

	void RunLocalMatch();
	void ReadCoordinatesSafely(unsigned int& outX, unsigned int& outY);
	void DrawBoard(const battlefield::Battlefield& field, bool isEnemy);

public:
	explicit ConsoleUserInterface(IDatabase& iDatabase) : IUserInterface(iDatabase) {}

	void PrintGameMenu() override;
};