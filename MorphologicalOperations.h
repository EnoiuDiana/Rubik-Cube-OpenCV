#pragma once

#include "Headers.h"
#include "HelperFunctions.h"

class MorphologicalOperations
{
public:
	Mat applyDilation(Mat src);
	Mat applyErosion(Mat src);
private:
	HelperFunctions helperFunctions = HelperFunctions();
	std::vector<std::pair<int, int>> getStructuringElement();
};

