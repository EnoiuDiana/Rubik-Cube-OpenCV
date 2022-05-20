#include "stdafx.h"
#include "ProjectRubikCube.h"


Vec3b ProjectRubikCube::identifyColor(Color color) {
	switch (color) {
	case red: return Vec3b(0, 0, 255);
	case orange: return Vec3b(39, 127, 255);
	case blue: return Vec3b(255, 0, 0);
	case green: return Vec3b(0, 255, 0);
	case white: return Vec3b(255, 255, 255);
	case yellow: return Vec3b(0, 255, 255);
	}
}

MyPoint ProjectRubikCube::identifyStartingPoint(Color faceColor) {
	switch (faceColor) {
	case blue: return helperFunctions.initPoint(92, 23);
	case red: return helperFunctions.initPoint(23, 92);
	case white: return helperFunctions.initPoint(92, 92);
	case orange: return helperFunctions.initPoint(161, 92);
	case green: return helperFunctions.initPoint(92, 161);
	case yellow: return helperFunctions.initPoint(92, 230);
	}
}

int identifyNeededRotations(Color faceColor) {
	switch (faceColor) {
	case blue: return 1;
	case red: return 0;
	case white: return 1;
	case orange: return 1;
	case green: return 2;
	case yellow: return 2;
	}
}

std::vector<Color> rotateFace(std::vector<Color> allColorsInOrder) {
	//rotate counter clockwise
	std::vector<Color> rotatedFace;
	rotatedFace.push_back(allColorsInOrder.at(2));
	rotatedFace.push_back(allColorsInOrder.at(5));
	rotatedFace.push_back(allColorsInOrder.at(8));
	rotatedFace.push_back(allColorsInOrder.at(1));
	rotatedFace.push_back(allColorsInOrder.at(4));
	rotatedFace.push_back(allColorsInOrder.at(7));
	rotatedFace.push_back(allColorsInOrder.at(0));
	rotatedFace.push_back(allColorsInOrder.at(3));
	rotatedFace.push_back(allColorsInOrder.at(6));
	return rotatedFace;
}

std::vector<Color> rotateFaceNTimes(std::vector<Color> faceToRotate, int n) {
	if (n == 1) {
		return rotateFace(faceToRotate);
	}
	else if (n == 2) {
		std::vector<Color> rotatedFace;
		rotatedFace = rotateFace(faceToRotate);
		return rotateFace(rotatedFace);
	}
	else if (n == 3) {
		std::vector<Color> rotatedFace1;
		std::vector<Color> rotatedFace2;
		rotatedFace1 = rotateFace(faceToRotate);
		rotatedFace2 = rotateFace(rotatedFace1);
		return rotateFace(rotatedFace2);
	}

	return faceToRotate;
}

void ProjectRubikCube::projectFace(Mat_<Vec3b> result, int start_x, int start_y, std::vector<Color> allColorsInOrder, Color faceColor) {

	int sx = start_x;
	int sy = start_y;
	int index = 0;

	std::vector<Color> faceToProject = rotateFaceNTimes(allColorsInOrder, identifyNeededRotations(faceColor));

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {

			Color currentColor = faceToProject.at(index);

			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					result.at<Vec3b>(sx + i, sy + j) = identifyColor(currentColor);
				}
			}

			sy += 23;
			index++;
		}
		sx += 23;
		sy = start_y;
	}

}

void ProjectRubikCube::projectRubikCube(std::map<Color, std::vector<Color>> facesInfo) {

	Mat_<Vec3b> result(300, 350);

	for (auto& faceInfo : facesInfo) {

		MyPoint stratingPoint = identifyStartingPoint(faceInfo.first);

		//todo modify list allColors
		projectFace(result, stratingPoint.x, stratingPoint.y, faceInfo.second, faceInfo.first);
	}

	imshow("result", result);
	waitKey(0);

}

