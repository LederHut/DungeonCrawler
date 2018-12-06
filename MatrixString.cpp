#include "MatrixString.h"

//FIX: Something is wrong with the generation of the Strings.
MatrixString::MatrixString(SMALL_RECT dimensions, bool growth)
	: Entity(dimensions),
	  Growth(growth)

{
	InitialLeft = Dimensions.Left;

	Length = 1;
	Heigth = Dimensions.Bottom - Dimensions.Top;

	Active = 1;

	MainOutBuffer.resize(Heigth);

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> distrbution(33,122);

	for (char& n : MainOutBuffer)
	{
		n = static_cast<char>(distrbution(gen));
	}
}

MatrixString::~MatrixString()
{
	delete this;
}

void MatrixString::Update()
{

	if (Growth)
	{



	}
	else
	{
		unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

		std::default_random_engine gen(seed);

		std::uniform_int_distribution<unsigned int> maindistrbution(0, (unsigned int)MainOutBuffer.size());
		std::uniform_int_distribution<int> chardistrbution(33, 122);

		MainOutBuffer[maindistrbution(gen)] = static_cast<char>(chardistrbution(gen));

		Dimensions.Top++;
		Dimensions.Bottom++;

	}

	if (Dimensions.Bottom == MAX_Y+1)
	{

		if(!MainOutBuffer.empty())
			MainOutBuffer.pop_back();

		Dimensions.Bottom--;
		Heigth--;

		if (MainOutBuffer.empty())
		{
			Active = 0;
		}

	}

}

void MatrixString::RePopulateMatrixString()
{
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine gen(seed);
	std::uniform_int_distribution<SHORT> ascii(33, 122),
										 ydes(0, 12),
										 xdes(1,3);

	std::uniform_int_distribution<int> heigthdes(1, 37);

	Shift = InitialLeft == 0 ? true : false;
	Shift = InitialLeft == MAX_X ? false : true;

	SHORT y(ydes(gen)),
		  x(Shift ? 1: -1);

	Shift = Shift ? false : true;

	int heigth(heigthdes(gen));

	Heigth = heigth;

	for (char& n : MainOutBuffer)
	{
		n = static_cast<char>(ascii(gen));
	}

	Dimensions = { InitialLeft + x,y , (InitialLeft + x) + 1,y + (SHORT)Heigth };

	MainOutBuffer.resize(Heigth);

	Active = true;
}
