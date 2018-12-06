#pragma once
#include "Entity.h"

class Player :
	public Entity
{
private:

	COLOR_INFO ColorInfo;

	SMALL_RECT Boundaries;

public:

	Player(SMALL_RECT pos, std::string indentifier,WORD attribute, bool b = 0);
	~Player();

	void Update() override;

	inline void SetBoundaries(SMALL_RECT coord) { Boundaries = coord; ColorInfo.Coord.X += coord.Left; ColorInfo.Coord.Y += coord.Top; }

	inline SMALL_RECT* GetPToDimensions() { return &Dimensions; }
	inline COLOR_INFO GetColorInfo() { return ColorInfo; }

private:

	void Movement();

};

