#pragma once

#include "Utility.h"

class TextWindow
{
private:

	WINDOW_INFORMATION WinInfo;

	std::vector<size_t> StringLengthHistory;

	unsigned TextHistory;

public:

	TextWindow(std::string, SMALL_RECT);
	~TextWindow();

	void WriteLine(std::string);
	void WriteText(std::string);
	void WriteStaticText(STATIC_TEXT);

	inline void SetActive(bool b) { WinInfo.Active = b; }

	inline WINDOW_INFORMATION* GetWinInfo() { return &WinInfo; }

	inline void Move() {

						if (WinInfo.OuterDimensions.Right == MAX_X)
						{
							WinInfo.OuterDimensions.Right = WinInfo.OuterLength;
							WinInfo.InnerDimensions.Right = WinInfo.InnerLength;
						}
						if (WinInfo.OuterDimensions.Left == MAX_X)
						{
							WinInfo.OuterDimensions.Left = 0;
							WinInfo.InnerDimensions.Left = 1;
						}
						WinInfo.OuterDimensions.Left++;
						WinInfo.OuterDimensions.Right++;
						WinInfo.InnerDimensions.Left++;
						WinInfo.InnerDimensions.Right++;
	}

private:

	void DoLine(std::string);
	void DoLine(STATIC_TEXT);
	void DoText(std::string);
};

