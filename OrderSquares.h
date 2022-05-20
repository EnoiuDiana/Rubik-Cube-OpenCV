#pragma once
#include "Headers.h"
#include "HelperFunctions.h"

class OrderSquares
{
public:
	std::pair<Color, std::vector<Color>> getColorsInOrderForOneFace(std::vector<std::pair<MyPoint, Color>> initialOrder);
	std::map<Color, std::vector<Color>> getColorsInOrderForTwoFaces(std::vector<std::pair<MyPoint, Color>> initialOrder);
private:
	HelperFunctions helperFunctions = HelperFunctions();
};

