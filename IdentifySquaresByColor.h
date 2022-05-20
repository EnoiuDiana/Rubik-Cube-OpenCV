#pragma once


#include "HelperFunctions.h"
#include "ImageColorTransformations.h"
#include "Headers.h"
#include "MorphologicalOperations.h"
#include "ImageColorTransformations.h"

class IdentifySquaresByColor
{
public:
	void identifyRubikCubeSquaresByColorsWithHSV(HsvMat hsvMat, Mat img);
	std::map<Color, Mat> identifyRubikCubeSquaresByColorsWithYuv(YuvMat yuvMat, Mat img, bool showProgress);
private:
	MorphologicalOperations morphologicalOperations = MorphologicalOperations();
	ImageColorTransformations imageColorTransformations = ImageColorTransformations();
};

