
#include <iostream>

#include "TextWindow.h"
#include "MenuWindow.h"
#include "GraphicWindow.h"
#include "ConsoleHandling.h"
#include "MenuElement.h"
#include "Player.h"

SMALL_RECT  temp = { 80,5 , 120,15 };		// {x,y , x,y} or {Left,Top , Right,Bottom}

ConsoleHandling chWindow;

int main()
{	
	

	MenuWindow mw("Thall'akshur", { 20,20 , 60,30 });

	MenuWindow mwe("Thall'akshur", { 20,20 , 60,30 });

	MenuElement mes("SAWAS", "n", { 5,0 , 0,0 });
	mes.SetNextWindow(&mw);
	mwe.AddMenuElement(&mes);

	MenuElement me("NEXT", "n", { 0,0 , 0,0 });
	me.SetNextWindow(&mwe);
	mw.AddMenuElement(&me);

	TextWindow txtwin("Moras'vankas", temp);

	chWindow.AddWindow(&mwe);
	chWindow.AddWindow(&mw);
	chWindow.AddWindow(&txtwin);

	while (true)
	{
		chWindow.Update();

		txtwin.WriteText("Naskor");

		//Sleep(100);
	}

	//Cleanup
	
	return 0;
}