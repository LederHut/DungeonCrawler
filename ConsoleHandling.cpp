
#include "ConsoleHandling.h"


ConsoleHandling::ConsoleHandling()
	:ConsoleDimension	({ MAX_X , MAX_Y }),
	 dwSize				(MAX_X * MAX_Y),
	 bState				(1),
	 RecordsRead		(0),
	 LastMenuWindow		(&bPlaceHolder),
	 LastMenuElement    (&bPlaceHolder),
	 NextMenuWindow     (0),
	
	 hConsoleOut		(GetStdHandle(STD_OUTPUT_HANDLE)),
	 _hConsoleOut		(GetStdHandle(STD_OUTPUT_HANDLE)),
	 hConsoleIn			(GetStdHandle(STD_INPUT_HANDLE))
	 
{
	if (hConsoleOut == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return;
	}

	SetConsoleActiveScreenBuffer(hConsoleOut);
	ConsoleSetup(hConsoleOut);
	SetWindow(ConsoleDimension);
	SetConsoleTitle("Dungeon Crawler");

	MainOutBuffer.resize(dwSize, ' ');
}

ConsoleHandling::~ConsoleHandling()
{

}

void ConsoleHandling::AddWindow(TextWindow* window)
{
	pTextWindows.push_back(window);
}
void ConsoleHandling::AddWindow(MenuWindow* window)
{
	pMenuWindows.push_back(window);
}
void ConsoleHandling::AddWindow(GraphicWindow* window)
{
	pGraphicWindows.push_back(window);
}

void ConsoleHandling::Update()
{
	GetConsoleInput();
	EvaluateInput();

	UpdateGraphicWindows();
	UpdateTextWindows();
	UpdateMenuWindows();
	
	ToConsoleOut();

	//Cleanup
	MainOutBuffer = ' ';
	MainOutBuffer.resize(dwSize, ' ');
	std::fill_n(PressedKeys, 26, 0);
}

void ConsoleHandling::GetConsoleInput()
{
		INPUT_RECORD ir[MAX_INPUTS_READ];
		if (!ReadConsoleInput(hConsoleIn,        // input buffer handle 
							  ir,				 // buffer to read into
							  MAX_INPUTS_READ,	 // size of read buffer
							  &RecordsRead))	 // number of records read
		{
			printf("ReadConsoleInput error (%d)", GetLastError());
			return;
		}
		std::copy(ir, ir + MAX_INPUTS_READ, IR);
}

void ConsoleHandling::EvaluateInput()
{
	for (size_t i = 0; i < RecordsRead; i++)
	{
		switch (IR[i].EventType)
		{
		default:
			break;
		case KEY_EVENT:
			ProccesKeyInput(IR[i].Event.KeyEvent, PressedKeys);
			break;
		case MOUSE_EVENT:
			break;
		}
	}
}

void ConsoleHandling::ProccesKeyInput(KEY_EVENT_RECORD ker,bool* pressedkeys)
{
	for (size_t i = 0; i < 26; i++)
	{
		if (ker.uChar.AsciiChar == ALPHABET[i])
		{
			pressedkeys[i] = true;
		}
	}
}

void ConsoleHandling::UpdateTextWindows()
{
	for (auto i = pTextWindows.begin(); i != pTextWindows.end(); i++)
	{
		TextWindow* tw(*i);

		WINDOW_INFORMATION* wi(tw->GetWinInfo());

		if (wi->Active)
		{
			SetOutBuffer(wi->MainOutBuffer,
						 wi->OuterDimensions,
						 wi->OuterLength,
						 wi->OuterHeigth);

			SetOutBuffer(wi->SecondOutBuffer,
						 wi->InnerDimensions,
						 wi->InnerLength,
						 wi->InnerHeigth);
		}
		else { return; }
	}
}

void ConsoleHandling::UpdateMenuWindows()
{
	bool pressedkeys[26];

	std::copy(PressedKeys, PressedKeys + 26, pressedkeys);

	for (auto i = pMenuWindows.begin(); i != pMenuWindows.end(); i++)
	{
		MenuWindow* mw(*i);

		WINDOW_INFORMATION* wi(mw->GetWinInfo());

		if (wi->Active)
		{
			SetOutBuffer(wi->MainOutBuffer,
						 wi->OuterDimensions,
						 wi->OuterLength,
						 wi->OuterHeigth);

			SetOutBuffer(wi->SecondOutBuffer,
						 wi->InnerDimensions,
						 wi->InnerLength,
						 wi->InnerHeigth);

			DoMenuWindowInput(mw,pressedkeys);
		}
		
	}

	
}

void ConsoleHandling::UpdateGraphicWindows()
{
	bool pressedkeys[26];

	std::copy(PressedKeys, PressedKeys + 26, pressedkeys);

	for (auto i = pGraphicWindows.begin(); i != pGraphicWindows.end(); i++)
	{
		GraphicWindow* gw(*i);

		WINDOW_INFORMATION* wi(gw->GetWinInfo());

		if (wi->Active)
		{
			DoGraphicWindowInput(gw,pressedkeys);

			SetOutBuffer(wi->MainOutBuffer,
						 wi->OuterDimensions,
						 wi->OuterLength,
						 wi->OuterHeigth);

			SetOutBuffer(wi->SecondOutBuffer, 
						 wi->InnerDimensions,
						 wi->InnerLength,
						 wi->InnerHeigth);

			wi->SecondOutBuffer = "";
			wi->SecondOutBuffer.resize(wi->InnerHeigth * wi->InnerLength,' ');
		}
		else { return; }

	}
}

//FIX: Somthing is still wrong with the way this gets input maybe.
//FIX: Using the same Identifier on differnt menuwindows (as long the same Identifier isn't schown on screen Identifier can be used more then once)
//     doesn't quite work. 
void ConsoleHandling::DoMenuWindowInput(MenuWindow* thismw, bool* pressedkeys) 
{																			 	
	std::vector<MenuElement*> thismes(thismw->GetMenuElements());

	WINDOW_INFORMATION* thiswi(thismw->GetWinInfo());

	for (auto i = thismes.begin(); i != thismes.end(); i++)
	{
		MenuElement* thisme(*i);

		MenuWindow* nextmw(static_cast<MenuWindow*>(thisme->_GetNextWindow()));

		WINDOW_INFORMATION* nextwi(nextmw->GetWinInfo());

		if (Utility::IsKeyPressed(*(thisme->GetIdentifier().c_str()), pressedkeys))
		{
			thiswi->Active = false;
			nextwi->Active = true;
		}

		if (nextwi->Active)
		{
			SetOutBuffer(nextwi->MainOutBuffer,
						 nextwi->OuterDimensions,
						 nextwi->OuterLength,
						 nextwi->OuterHeigth);

			SetOutBuffer(nextwi->SecondOutBuffer,
						 nextwi->InnerDimensions,
						 nextwi->InnerLength,
						 nextwi->InnerHeigth);
		}
	}
}

void ConsoleHandling::DoGraphicWindowInput(GraphicWindow* gw, bool* pressedkeys)
{
	Player* player(gw->GetPlayer());

	SMALL_RECT* sm(player->GetPToDimensions());

	WINDOW_INFORMATION* wi(gw->GetWinInfo());

	if (Utility::IsKeyPressed('w',pressedkeys))
	{
		sm->Top--;
	}
	else if (Utility::IsKeyPressed('a',pressedkeys))
	{
		sm->Left--;
	}
	else if (Utility::IsKeyPressed('s', pressedkeys))
	{
		sm->Top++;
	}
	else if (Utility::IsKeyPressed('d', pressedkeys))
	{
		sm->Left++;
	}

	Utility::SetOutBuffer(wi->SecondOutBuffer,
						  wi->InnerLength,
					 	  player->GetMainOutBuffer(),
						  player->GetDimensions(),
						  player->GetLength(),
						  player->GetHeigth());
}

void ConsoleHandling::SetOutBuffer(OutBuffer outbuffer, SMALL_RECT destination, unsigned length, unsigned height)
{
	std::string temp;

	for (size_t y = 0; y < height; y++)
	{
		temp.assign(outbuffer, y * length, length +1);

		for (size_t x = 0; x < temp.length(); x++)
		{
			MainOutBuffer[((y + destination.Top) * MAX_X) + ((x + destination.Left))] = temp[x];
		}
		temp.empty();
	}

}

void ConsoleHandling::ToConsoleOut()
{

	if (bState)
	{
		ClearConsole(_hConsoleOut);
		if (!WriteConsoleOutputCharacter(_hConsoleOut,
			MainOutBuffer.c_str(),
			MainOutBuffer.length(),
			{ 0, 0 },
			&dwSize))
		{
			printf("WriteConsoleOutputCharacter error (%d)", GetLastError());
			return;
		}

		SetConsoleActiveScreenBuffer(_hConsoleOut);

		bState = 0;
	}
	else if (!bState)
	{
		ClearConsole(hConsoleOut);
		if (!WriteConsoleOutputCharacter(hConsoleOut,
			MainOutBuffer.c_str(),
			MainOutBuffer.length(),
			{ 0, 0 },
			&dwSize))
		{
			printf("WriteConsoleOutputCharacter error (%d)", GetLastError());
			return;
		}

		SetConsoleActiveScreenBuffer(hConsoleOut);

		bState = 1;
	}

}

void ConsoleHandling::SetWindow(_COORD cSize)
{
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = cSize.Y - 1;
	Rect.Right = cSize.X - 1;

	SetConsoleScreenBufferSize(hConsoleOut, cSize);
	SetConsoleWindowInfo(hConsoleOut, TRUE, &Rect);
}

void ConsoleHandling::ConsoleSetup(HANDLE &hStdOutput)
{
	

	/*if (!SetConsoleDisplayMode(hStdOutput, NULL , &CSBI.dwSize))
	{
		printf("SetConsoleDisplayMode error (%d)",GetLastError());
		return;
	}*/
	if (!SetConsoleMode(hStdOutput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
	{
		printf("SetConsoleMode error (%d)",GetLastError());
		return;
	}
	/*if (!SetConsoleScreenBufferSize(hStdOutput, ConsoleScreenDimensions))
	{
		printf("SetConsoleScreenBufferSize error (%d)", GetLastError());
		return;
	}*/

	SetConsoleCursorInfo(hStdOutput, &cci);

}

void ConsoleHandling::ClearConsole(HANDLE &handle)
{
	DWORD Size(MAX_X * MAX_Y);
	
	if (!FillConsoleOutputCharacter(handle,
		' ',
		0,
		{ 0, 0 },
		&Size))
	{
		printf("FillConsoleOutputCharacter error (%d)", GetLastError());
		return;
	}
}