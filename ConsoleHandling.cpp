#include "pch.h"
#include "ConsoleHandling.h"


ConsoleHandling::ConsoleHandling():
	ConsoleDimension	({ MAX_X , MAX_Y }),
	dwSize				(MAX_X * MAX_Y),
	bState				(1),
	bClear				(1),
	RecordsRead			(0),

	hConsoleOut			(GetStdHandle(STD_OUTPUT_HANDLE)),
	_hConsoleOut		(GetStdHandle(STD_OUTPUT_HANDLE)),
	hConsoleIn			(GetStdHandle(STD_INPUT_HANDLE))
	
{
	if (hConsoleOut == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return;
	}

	cci.bVisible = false;

	SetConsoleActiveScreenBuffer(hConsoleOut);
	ConsoleSetup(hConsoleIn);
	SetWindow(ConsoleDimension);
	SetConsoleTitle("Dungeon Crawler");

	InputThread.push_back(std::thread(&Input::PeekInput, &Input(), std::ref(hConsoleIn)));

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
	Attributes.insert(Attributes.end(), window->GetColorInfosBegin(), window->GetColorInfoEnd());
	pMenuWindows.push_back(window);
}
void ConsoleHandling::AddWindow(GraphicWindow* window)
{
	pGraphicWindows.push_back(window);
}

void ConsoleHandling::AddMatrixStrings(unsigned int amount, bool growth)
{
	amount = amount > MAX_Y ? 200 : amount;

	for (size_t i = 0; i < amount; i++)
	{
		unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

		std::default_random_engine gen(seed);
		std::uniform_int_distribution<SHORT> xdes(0, MAX_X),
										     ydes(0, 12),
										     lendes(3, 10);

		SHORT x(xdes(gen)),
			  y(ydes(gen));

		if (std::find(UsedXPos.begin(),UsedXPos.end(),x) != UsedXPos.end())
			Utility::FindNewValue(UsedXPos, x);

		MatrixString* ms = new MatrixString({ x,growth? 0 : y , x + 1,y + lendes(gen) }, growth);

		pMatrixStrings.push_back(ms);
		UsedXPos.push_back(x);
	}
}

void ConsoleHandling::Update()
{
	//Detach input thread.
	DetachThread();
	
	//Update the information.
	UpdateGraphicWindows();
	UpdateTextWindows();
	UpdateMenuWindows();
	UpdateMatrixStrings();

	//Draw everything that is in MainOutBuffer to the console.
	ToConsoleOut();

	//Cleanup
	ClearInputBufferThread();
	Attributes.clear();
	MainOutBuffer = ' ';
	MainOutBuffer.resize(dwSize, ' ');
}

void ConsoleHandling::UpdateTextWindows()
{
	for (auto i = pTextWindows.begin(); i != pTextWindows.end(); i++)
	{
		TextWindow* tw(*i);

		WINDOW_INFORMATION* wi(tw->GetWinInfo());

		if (wi->Active)
		{
			SetMainBuffer(wi->MainOutBuffer,
						 wi->OuterDimensions,
						 wi->OuterLength,
						 wi->OuterHeigth);

			SetMainBuffer(wi->SecondOutBuffer,
						 wi->InnerDimensions,
						 wi->InnerLength,
						 wi->InnerHeigth,
						 0);
		}
		else { return; }
	}
}

//EDIT: The ProccesInput func should not be called after the buffer has ben set
//		because now the changes of the current input will be made in the next frame what I think is not optimal.
void ConsoleHandling::UpdateMenuWindows()
{

	for (auto i = pMenuWindows.begin(); i != pMenuWindows.end(); i++)
	{
		MenuWindow* mw(*i);

		WINDOW_INFORMATION* wi(mw->GetWinInfo());

		if (wi->Active)
		{
			SetMainBuffer(wi->MainOutBuffer,
						  wi->OuterDimensions,
						  wi->OuterLength,
						  wi->OuterHeigth);

			SetMainBuffer(wi->SecondOutBuffer,
						  wi->InnerDimensions,
						  wi->InnerLength,
						  wi->InnerHeigth,
						  0);
		}
		
		if (!KeyEvents.empty() && MouseEvents.empty())
			mw->ProccesInput();
	}

	
}

void ConsoleHandling::UpdateGraphicWindows()
{

	for (auto i = pGraphicWindows.begin(); i != pGraphicWindows.end(); i++)
	{
		GraphicWindow* gw(*i);

		WINDOW_INFORMATION* wi(gw->GetWinInfo());

		if (wi->Active)
		{
			gw->Update();

			Attributes.push_back(gw->GetPlayer()->GetColorInfo());

			SetMainBuffer(wi->MainOutBuffer,
						  wi->OuterDimensions,
						  wi->OuterLength,
						  wi->OuterHeigth);

			SetMainBuffer(wi->SecondOutBuffer,
						  wi->InnerDimensions,
						  wi->InnerLength,
						  wi->InnerHeigth,
						  0);

			wi->SecondOutBuffer = "";
			wi->SecondOutBuffer.resize(wi->InnerHeigth * wi->InnerLength,' ');
		}
		else { return; }

	}
}

void ConsoleHandling::UpdateMatrixStrings()
{
	for (auto ms : pMatrixStrings)
	{

		ms->Update();

		if (ms->GetActive())
		{

			SetMainBuffer(ms->GetMainOutBuffer(),
						  ms->GetDimensions(),
						  ms->GetLength(),
						  ms->GetHeigth(),
						  0);
		}
		else
		{

			ms->RePopulateMatrixString();

		}

	}
}

void ConsoleHandling::SetMainBuffer(OutBuffer outbuffer, SMALL_RECT destination, unsigned length, unsigned height, bool ismain)
{
	std::string temp;

	for (size_t y = 0; y < height; y++)
	{
		temp.assign(outbuffer, y * length, length + ismain);

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

		for (COLOR_INFO ci : Attributes)
		{
			if (!WriteConsoleOutputAttribute(_hConsoleOut,
				ci.Attribute,
				ci.Length,
				ci.Coord,
				&WrittenAttributes))
			{
				printf("WriteConsoleOutputAttribute error (%d)", GetLastError());
				return;
			}
		}

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

		for (COLOR_INFO ci : Attributes)
		{
			if (!WriteConsoleOutputAttribute(hConsoleOut,
				ci.Attribute,
				ci.Length,
				ci.Coord,
				&WrittenAttributes))
			{
				printf("WriteConsoleOutputAttribute error (%d)", GetLastError());
				return;
			}
		}

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

void ConsoleHandling::ConsoleSetup(HANDLE &hstdin)
{
	

	/*if (!SetConsoleDisplayMode(hStdOutput, NULL , &CSBI.dwSize))
	{
		printf("SetConsoleDisplayMode error (%d)",GetLastError());
		return;
	}*/
	if (!SetConsoleMode(hstdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
	{
		printf("SetConsoleMode error (%d)",GetLastError());
		return;
	}
	/*if (!SetConsoleScreenBufferSize(hStdOutput, ConsoleScreenDimensions))
	{
		printf("SetConsoleScreenBufferSize error (%d)", GetLastError());
		return;
	}*/

	SetConsoleCursorInfo(hstdin, &cci);

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

	/*if (!FillConsoleOutputAttribute(handle,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		dwSize,
		{ 0, 0 },
		&WrittenAttributes))
	{
		printf("FillConsoleOutputCharacter error (%d)", GetLastError());
		return;
	}*/
}

void ConsoleHandling::ClearInputBufferThread()
{
	if (bClear)
	{
		bClear = false;
		ClearInputBuffer(hConsoleIn);
	}
		
}

void ConsoleHandling::DetachThread()
{
	if (InputThread.front().joinable() && bFree)
	{
		bClear = true;
		bFree = false;
		InputThread.front().detach();
		InputThread.pop_back();
		InputThread.push_back(std::thread(&Input::PeekInput, &Input(), std::ref(hConsoleIn)));
	}
}
