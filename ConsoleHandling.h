#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>

#include "Utility.h"
#include "TextWindow.h"
#include "MenuWindow.h"
#include "GraphicWindow.h"
#include "MatrixString.h"
#include "Input.h"


class ConsoleHandling : 
	public Input
{
private:


	std::vector<TextWindow*>		pTextWindows;
	std::vector<MenuWindow*>		pMenuWindows;
	std::vector<GraphicWindow*>		pGraphicWindows;
	std::vector<MatrixString*>		pMatrixStrings;
	
	std::vector<std::thread>		InputThread;

	COORD							ConsoleDimension;

	CONSOLE_SCREEN_BUFFER_INFO		csbi;
	CONSOLE_CURSOR_INFO				cci;

	INPUT_RECORD					IR[MAX_INPUT_READS];

	HANDLE							hConsoleOut,
									_hConsoleOut,
									hConsoleIn;
	
	OutBuffer MainOutBuffer;

	std::vector<ON_KEY_PRESS_CALLBACK_FUNC> EntityCallbacks;

	std::vector<bool> ActiveEntitys;

	std::vector<COLOR_INFO> Attributes;

	DWORD dwSize,
		  RecordsRead,
		  WrittenAttributes;

	bool bState,
		 bClear;
	
public:

	ConsoleHandling();
	~ConsoleHandling();

	
	void AddWindow(TextWindow*);
	void AddWindow(MenuWindow*);
	void AddWindow(GraphicWindow*);
	void AddMatrixStrings(unsigned int);
	

	void Update();

	inline DWORD GetRecordsRead() { return RecordsRead; }
	inline std::vector<bool> GetActiveEntitys() { return ActiveEntitys; }

private:


	void UpdateTextWindows();
	void UpdateMenuWindows();
	void UpdateGraphicWindows();
	void UpdateMatrixStrings();

	void SetMainBuffer(OutBuffer, SMALL_RECT, const unsigned, const unsigned, bool ismain = 1);
	void SetWindow(_COORD);
	void ConsoleSetup(HANDLE&);
	void ClearConsole(HANDLE&);
	void ClearInputBufferThread();
	void DetachThread();

	void ToConsoleOut();
	
};