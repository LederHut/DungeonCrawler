#pragma once

#include "Input.h"
#include "Player.h"
#include "Terrain.h"

class GraphicWindow:
	public Input
{
private:

	WINDOW_INFORMATION WinInfo;

	Player* _Player;

	std::vector<Terrain> TerVec;

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