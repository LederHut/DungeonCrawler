#include "pch.h"
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
	player->SetBoundaries(WinInfo.InnerDimensions);
	_Player = player;
}

void GraphicWindow::Update()
{
	UpdatePlayer();
	

}

void GraphicWindow::UpdatePlayer()
{

	_Player->Update();

	Utility::SetOutBuffer(WinInfo.SecondOutBuffer,
						  WinInfo.InnerLength,
						  _Player->GetMainOutBuffer(),
						  _Player->GetDimensions(),
						  _Player->GetLength(),
						  _Player->GetHeigth());

}
