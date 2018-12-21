
#include "pch.h"
#include "ConsoleHandling.h"


int main()
{
	
	ConsoleHandling chWindow;

	Terrain Floor({0,0 , 0,0}, "F", FOREGROUND_GREEN);

	MenuElement me1("Floor", "S", { 1,1 , 0,0 });
	me1.SetTerrain(&Floor);

	MenuWindow TerrainMenu("Terrain Menu", { 0,0 , 30,20 });
	TerrainMenu.AddMenuElement(&me1);


	chWindow.AddWindow(&TerrainMenu);

	while (true)
	{
		chWindow.Update();
	}

	return 0;
}