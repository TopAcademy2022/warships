#include <iostream>

#include "src/console-user-interface.h"
#include "src/notepad-database.h"

int main()
{
	NotepadDatabase database;
	ConsoleUserInterface menu(database);

	menu.PrintGameMenu();
	return 0;
}
