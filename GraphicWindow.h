#pragma once

#include "Utility.h"
#include "Entity.h"

class GraphicWindow
{
private:
	WINDOW_INFORMATION WinInfo;

public:

	GraphicWindow(std::string title, SMALL_RECT dimensions);
	~GraphicWindow();

	inline WINDOW_INFORMATION* GetWinInfo() { return &WinInfo; }

private:

};

