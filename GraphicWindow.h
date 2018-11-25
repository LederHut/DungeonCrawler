#pragma once

#include "Utility.h"
#include "Player.h"

class GraphicWindow
{
private:

	WINDOW_INFORMATION WinInfo;

	SMALL_RECT GraphicDimensions;

	unsigned GraphicHeight,
			 GraphicLength;

	Player* _Player;

public:

	GraphicWindow(std::string, SMALL_RECT);
	~GraphicWindow();
	
	void SetPlayer(Player*);

	inline WINDOW_INFORMATION* GetWinInfo() { return &WinInfo; }
	inline Player* GetPlayer() { return _Player; }

private:

};

