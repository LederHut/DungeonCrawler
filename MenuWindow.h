#pragma once

#include "Utility.h"
#include "Input.h"
#include "TextWindow.h"
#include "MenuElement.h"



class MenuWindow : 
	public Input
{
private:

	WINDOW_INFORMATION			WinInfo;

	IN_WINDOW_TEXTFIELD_INFO	TextfieldInfo;

	std::vector<MenuElement*>	MenuElements;

	bool* PressedKeys;


public:

	MenuWindow(std::string, SMALL_RECT,bool active = 1);
	~MenuWindow();

	void AddMenuElement(MenuElement*);

	void ProccesInput();

	inline void WriteToTextfield(std::string text)				{ AddText(); }

	inline void SetActive(bool b)								{ WinInfo.Active = b; }
	inline void SetTextfield(SMALL_RECT dimensions)				{ TextfieldInfo.SetTextfield(dimensions); }

	inline WINDOW_INFORMATION* GetWinInfo()						{ return &WinInfo; }
	inline std::vector<MenuElement*> GetMenuElements()			{ return MenuElements; }

private:

	void AddText();

};

