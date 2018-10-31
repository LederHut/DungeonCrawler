#pragma once

#include "Utility.h"

class Entity
{
private:

	
	OutBuffer MainOutBuffer;

	std::string Indentifier;

	unsigned OuterLength,
			 OuterHeigth,
			 InnerLength,
			 InnerHeigth,
		     Color;

	bool Active;

	SMALL_RECT OuterDimensions,
			   InnerDimensions;

	std::vector<ON_KEY_PRESS_CALLBACK_FUNC> CallBackFun;


public:

	Entity();
	Entity(OutBuffer, SMALL_RECT, FLAG, unsigned color = 0, std::string identifier = " ");
		
	~Entity();
	inline void AddCallback(ON_KEY_PRESS_CALLBACK_FUNC cbfun) { CallBackFun.push_back(cbfun); }

	inline OutBuffer GetMainOutBuffer() { return MainOutBuffer; }
	inline SMALL_RECT GetOuterDimensions() { return OuterDimensions; }
	inline SMALL_RECT GetInnerDimensions() { return InnerDimensions; }
	inline unsigned GetInnerHeigth() { return InnerHeigth; }
	inline unsigned GetInnerLength() { return InnerLength; }
	inline unsigned GetOuterHeigth() { return OuterHeigth; }
	inline unsigned GetOuterLength() { return OuterLength; }
	inline unsigned GetColor() { return Color; }
	inline std::vector<ON_KEY_PRESS_CALLBACK_FUNC> GetCallback() { return CallBackFun; }

private:

};

