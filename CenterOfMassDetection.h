#pragma once

#include "Headers.h"
#include "HelperFunctions.h"

class CenterOfMassDetection
{
public:
	std::vector<MyPoint> callBFSToFindCenterOfMass(Mat src, bool showProgress);
private:
	HelperFunctions helperFunctions = HelperFunctions();
};

