#include "GraphicWindow.h"



GraphicWindow::GraphicWindow(std::string title, SMALL_RECT dimensions)
	:WinInfo(title, dimensions)
{
	Utility::DoBorder(WinInfo.Title, WinInfo.MainOutBuffer, WinInfo.OuterDimensions);
}

GraphicWindow::~GraphicWindow()
{
}

void GraphicWindow::SetPlayer(Player* player)
{
	_Player = player;
}
