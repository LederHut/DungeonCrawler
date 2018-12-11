
#include "Input.h"
#include "TextWindow.h"
#include "MenuWindow.h"
#include "GraphicWindow.h"
#include "ConsoleHandling.h"
#include "MenuElement.h"
#include "Player.h"
#include "MatrixString.h"

SMALL_RECT  temp = { 80,20 , 120,30 };		// {x,y , x,y} or {Left,Top , Right,Bottom}

ConsoleHandling chWindow;

int main()
{	
	

	Player player({0,0 , 0,0},"@",FOREGROUND_BLUE,true);

	MenuElement me1("output", "o", { 1,1 , 0,0}),
				me2("input", "i", { 1,1 , 0,0 }),
				me3("throughput","n", { 1,2 , 0,0 });

	MenuWindow tw("input",temp,0);
	tw.AddMenuElement(&me1);
	me2.SetNextWindow(&tw);
	me3.SetNextWindow(&tw);

	MenuWindow mw("output", temp);
	mw.AddMenuElement(&me3);
	mw.AddMenuElement(&me2);
	me1.SetNextWindow(&mw);

	GraphicWindow gw("Titan",{ 10,5 , 110,35 });
	gw.SetPlayer(&player);

	chWindow.AddWindow(&mw);
	chWindow.AddWindow(&tw);
	chWindow.AddWindow(&gw);

	//chWindow.AddMatrixStrings(2);

	while (true)
	{
		chWindow.Update();

		//Sleep(25);
	}

	//Cleanup
	
	return 0;
}