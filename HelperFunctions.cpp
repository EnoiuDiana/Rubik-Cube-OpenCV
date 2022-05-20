#include "stdafx.h"
#include "HelperFunctions.h"


float HelperFunctions::computeMaxValue(float r, float g, float b) {
	float firstMax = max(r, g);
	return max(firstMax, b);
}

float HelperFunctions::computeMinValue(float r, float g, float b) {
	float firstMin = min(r, g);
	return min(firstMin, b);
}

bool HelperFunctions::isInsideImg(int imgRows, int imgCols, int i, int j) {
	if (i >= 0 && i < imgRows) {
		if (j >= 0 && j < imgCols) {
			return true;
		}
	}
	return false;
}

void HelperFunctions::computeHistogram(Mat img, int* hist) {
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			hist[img.at<uchar>(i, j)]++;
		}
	}
}

MyPoint HelperFunctions::initPoint(int x, int y) {
	MyPoint point1;
	point1.x = x;
	point1.y = y;
	return point1;
}