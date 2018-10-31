#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>

#include "Utility.h"
#include "TextWindow.h"
#include "MenuWindow.h"
#include "GraphicWindow.h"


class ConsoleHandling
{
private:


	std::vector<TextWindow*>		pTextWindows;
	std::vector<MenuWindow*>		pMenuWindows;
	std::vector<GraphicWindow*>		pGraphicWindows;

	COORD							ConsoleDimension;

	CONSOLE_SCREEN_BUFFER_INFO		csbi;
	CONSOLE_CURSOR_INFO				cci;

	INPUT_RECORD					IR[MAX_INPUTS_READ];

	HANDLE							hConsoleOut,
									_hConsoleOut,
									hConsoleIn;

	OutBuffer MainOutBuffer;

	std::vector<ON_KEY_PRESS_CALLBACK_FUNC> EntityCallbacks;

	std::vector<bool> ActiveEntitys;

	DWORD dwSize,
		  RecordsRead,
		  NextMenuWindow;

	bool bPlaceHolder { 0 },
		 bState,
		 *LastMenuWindow,
	 	 *LastMenuElement,
		 PressedKeys[26];
	
public:

	ConsoleHandling();
	~ConsoleHandling();

	
	void AddWindow(TextWindow*);
	void AddWindow(MenuWindow*);
	void AddWindow(GraphicWindow*);
	

	void Update();

	inline DWORD GetRecordsRead() { return RecordsRead; }
	inline bool* GetPressedKeys() { return PressedKeys; }
	inline std::vector<bool> GetActiveEntitys() { return ActiveEntitys; }

private:

	
	void UpdateTextWindows();
	void UpdateMenuWindows();
	void UpdateGraphicWindows();

	void DoMenuWindowInput(MenuWindow*, bool*);
	void DoGraphicWindowInput(GraphicWindow*, bool*);

	void SetOutBuffer(OutBuffer, SMALL_RECT, const unsigned, const unsigned);
	void ProccesKeyInput(KEY_EVENT_RECORD, bool*);
	void SetWindow(_COORD);
	void ConsoleSetup(HANDLE&);
	void ClearConsole(HANDLE&);

	void ToConsoleOut();
	void GetConsoleInput();
	void EvaluateInput();
	
};