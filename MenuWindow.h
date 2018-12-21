#pragma once

//#include "Utility.h"
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

	std::vector<COLOR_INFO>		ColorInfos;

	MenuElement*				CurrSelect;

public:

	MenuWindow(std::string, SMALL_RECT,bool active = 1);
	~MenuWindow();

	void AddMenuElement(MenuElement* me);

	void ProccesInput();
	void HandleMenuKeyInput(MenuElement* me);
	void HandleMenuMouseInput(MenuElement* me);

	inline void WriteToTextfield(std::string text)				{ AddText(); }

	inline void SetActive(bool b)								{ WinInfo.Active = b; }
	inline void SetTextfield(SMALL_RECT dimensions)				{ TextfieldInfo.SetTextfield(dimensions); }

	inline auto GetColorInfoEnd()								{ return ColorInfos.end(); }
	inline auto GetColorInfosBegin()							{ return ColorInfos.begin(); }
	inline WINDOW_INFORMATION* GetWinInfo()						{ return &WinInfo; }
	inline std::vector<MenuElement*> GetMenuElements()			{ return MenuElements; }

private:

	void AddText();

};

