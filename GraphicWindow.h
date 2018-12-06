#pragma once

#include "Utility.h"
#include "Player.h"
#include "Input.h"

class GraphicWindow :
	public Input
{
private:

	WINDOW_INFORMATION WinInfo;

	Player* _Player;

public:

	GraphicWindow(std::string, SMALL_RECT);
	~GraphicWindow();
	
	void SetPlayer(Player*);

	void Update();

	inline WINDOW_INFORMATION* GetWinInfo() { return &WinInfo; }
	inline Player* GetPlayer() { return _Player; }

private:

	void UpdatePlayer();

};

