#pragma once
#include "Entitys.h"

class MenuElement : public Entitys
{
private:

	const std::string Identifier;

	void* NextWindow;

public:

	void SetNextWindow(void*);

	MenuElement(SMALL_RECT dimensoins, const std::string indentifier, OutBuffer titel);
	~MenuElement();

	inline std::string GetIdentifier() { return Identifier; }
	inline void* _GetNextWindow() {return NextWindow; }

private:



};

