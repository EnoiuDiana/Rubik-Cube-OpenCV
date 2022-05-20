#pragma once

#include "HelperFunctions.h"
#include "MorphologicalOperations.h"
#include "Headers.h"

class CannyEdgeDetection
{
public:

	Mat callCannyEdgeDetection(Mat src, bool showProgression);
	Mat applyFilterToImg(Mat src, Mat filter, bool showProgression); //used to amplify the edges detected with canny on the original colored image

private:

	HelperFunctions helperFunctions = HelperFunctions();
	MorphologicalOperations morphologicalOperations = MorphologicalOperations();

	struct sobel_result {
		Mat_<float> mag;
		Mat_<float> dir;
		Mat res;
	};

	sobel_result gradientSobel(Mat src);
	void callGradientConvo();
	int nonMaximaSuppression(float dir);
	Mat applyNonMaximaSuppression(Mat src, Mat_<float> direction, Mat_<float> magnitude);
	Mat callBFSForCanny(Mat src, int threshold_low, int threshold_high);

};