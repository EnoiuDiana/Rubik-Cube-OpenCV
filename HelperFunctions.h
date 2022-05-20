#pragma once

#include "Headers.h"

class HelperFunctions
{
public:
	float computeMaxValue(float r, float g, float b);
	float computeMinValue(float r, float g, float b);
	bool isInsideImg(int imgRows, int imgCols, int i, int j);
	void computeHistogram(Mat img, int* hist);
	MyPoint initPoint(int x, int y);

};

