#pragma once
#include "Entity.h"
#include "Terrain.h"

class MenuElement :
	public Entity
{
private:

	COLOR_INFO ColorInfo;

	std::string Identifier;

	SHORT IdPos,
		  CrossPos;

	void* NextWindow;

public:

	bool isSelected;

	void SetTerrain(Terrain* t);
	void SetNextWindow(void*);
	void Select();
	void UnSelect();

	MenuElement(OutBuffer titel, std::string indentifier, SMALL_RECT dimensoins);
	~MenuElement();

	inline void SetColorPos(SMALL_RECT dimensions) { ColorInfo.Coord = {dimensions.Left + ColorInfo.Coord.X, dimensions.Top + Dimensions.Top}; }

	inline bool GetisSelected() { return isSelected; }
	inline COLOR_INFO GetColorInfo() { return ColorInfo; }
	inline std::string GetIdentifier() { return Identifier; }
	inline void* _GetNextWindow() { return NextWindow; }

private:



};