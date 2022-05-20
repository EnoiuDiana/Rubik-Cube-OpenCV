#pragma once

#include "HelperFunctions.h"
#include "Headers.h"


class ImageColorTransformations
{

public:
	Mat rgbToGrayscaleImage(Mat img);
	Mat convertToBinary(Mat img);
	HsvMat rgbToHsvConversion(Mat img);
	YuvMat rgbToYuvConversion(Mat img);

private:
	HelperFunctions helperFunctions = HelperFunctions();
};

