
#include <iostream>

#include "TextWindow.h"
#include "MenuWindow.h"
#include "GraphicWindow.h"
#include "ConsoleHandling.h"
#include "MenuElement.h"
#include "Player.h"

SMALL_RECT  temp = { 80,5 , 120,15 },		// {x,y , x,y} or {Left,Top , Right,Bottom}
			temps = { 0,0 , 12,20 },
			tempss = { 10,5 , 180,30 };

std::string Map = { "123456712345671234567" };

//Entity ent("option", tempsss, MENU_ELEMENT, 0 , "a"),
//	     player("P", tempsss, IN_GAME_OBJECT),
//	     map(Map, tempsss, MAP);

ConsoleHandling chWindow;

int main()
{ 
	Player _player({ 10,5 , 0,0 },"@",1);

	TextWindow textwindow("Mordor", temps),
			   _textwindow("Son", { 13,0 , 25,12 });

	GraphicWindow graphicwindow("Game", tempss);
	graphicwindow.SetPlayer(&_player);

	MenuElement _menuelement({ 1,2 , 0,0 }, "b", "backward"),
				menuelement({ 0,2 , 0,0 }, "f", "forward"),
				MeToMenu_F({ 1,2 , 0,0 },"o","ToMenu_F"),
				MeToMenu_B({ 13,2 , 0,0 },"k","ToMenu_B"),
				test({ 1,4 , 0,0 },"l","Open_LORD");
	
	MenuWindow lord("LORD",temp,0);
	lord.AddMenuElement(&MeToMenu_B);
	test.SetNextWindow(&lord);


	MenuWindow menuwindowChose("TwoButtons", temp, 0);
	menuwindowChose.AddMenuElement(&MeToMenu_F);
	menuwindowChose.AddMenuElement(&MeToMenu_B);
	menuwindowChose.AddMenuElement(&test);
	_menuelement.SetNextWindow(&menuwindowChose);


	MenuWindow _menuwindow("Menu_B", temp, 0);
	_menuwindow.AddMenuElement(&_menuelement);
	menuelement.SetNextWindow(&_menuwindow);
	MeToMenu_B.SetNextWindow(&_menuwindow);

	

	MenuWindow menuwindow("Menu_F", temp);
	menuwindow.AddMenuElement(&menuelement);
	MeToMenu_F.SetNextWindow(&menuwindow);


	chWindow.AddWindow(&textwindow);
	chWindow.AddWindow(&_textwindow);

	chWindow.AddWindow(&menuwindow);
	chWindow.AddWindow(&_menuwindow);
	chWindow.AddWindow(&menuwindowChose);
	chWindow.AddWindow(&lord);

	chWindow.AddWindow(&graphicwindow);

	unsigned i(0);

	while (true)
	{
		chWindow.Update();

		textwindow.WriteText(std::to_string(sizeof(_menuwindow)) + ".bytes");

		Sleep(100);

		i++;
	}

	//Cleanup
	
	return 0;
}