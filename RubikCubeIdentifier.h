#pragma once

#include "Headers.h"
#include "CannyEdgeDetection.h"
#include "CenterOfMassDetection.h"
#include "HelperFunctions.h"
#include "IdentifySquaresByColor.h"
#include "ImageColorTransformations.h"
#include "MorphologicalOperations.h"
#include "OrderSquares.h"
#include "ProjectRubikCube.h"

class RubikCubeIdentifier
{
public:
	void callRubikCubeIdentifierUsingOneFace();
	void callRubikCubeIdentifierUsingTwoFaces();
	void identifySpectrumOfColors();
private:
	CannyEdgeDetection cannyEdgeDetection = CannyEdgeDetection();
	CenterOfMassDetection centerOfMassDetection = CenterOfMassDetection();
	ImageColorTransformations imageColorTransformations = ImageColorTransformations();
	IdentifySquaresByColor identifySquaresByColor = IdentifySquaresByColor();
	OrderSquares orderSquares = OrderSquares();
	ProjectRubikCube projectRubikCube = ProjectRubikCube();
};

