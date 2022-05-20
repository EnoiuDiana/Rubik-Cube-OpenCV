#pragma once

#include "Headers.h"
#include "HelperFunctions.h"

class ProjectRubikCube
{
public:
	void projectFace(Mat_<Vec3b> result, int start_x, int start_y, std::vector<Color> allColorsInOrder, Color faceColor);
	void projectRubikCube(std::map<Color, std::vector<Color>> facesInfo);
private:
	HelperFunctions helperFunctions = HelperFunctions();
	Vec3b identifyColor(Color color);
	MyPoint identifyStartingPoint(Color faceColor);
};

