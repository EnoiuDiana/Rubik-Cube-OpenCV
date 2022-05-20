#include "stdafx.h"
#include "OrderSquares.h"

bool sortbyrows(const std::pair<MyPoint, Color>& a,
	const std::pair<MyPoint, Color>& b)
{
	return (a.first.x < b.first.x);
}

bool sortbycols(const std::pair<MyPoint, Color>& a,
	const std::pair<MyPoint, Color>& b)
{
	return (a.first.y < b.first.y);
}

std::pair<Color, std::vector<Color>> OrderSquares::getColorsInOrderForOneFace(std::vector<std::pair<MyPoint, Color>> initialOrder) {
	std::vector<std::pair<MyPoint, Color>> orderedByRows;
	std::vector<Color> orderedColors;

	sort(initialOrder.begin(), initialOrder.end(), sortbyrows);

	for (int k = 0; k < 3; k++) {

		orderedByRows.push_back(initialOrder.at(k * 3 + 0));
		orderedByRows.push_back(initialOrder.at(k * 3 + 1));
		orderedByRows.push_back(initialOrder.at(k * 3 + 2));

		sort(orderedByRows.begin(), orderedByRows.end(), sortbycols);
		for (int i = 0; i < orderedByRows.size(); i++) {
			orderedColors.push_back(orderedByRows.at(i).second);
		}
		orderedByRows.clear();

	}

	//identify the color of the face as it is the same with color of the square in the center
	Color faceColor = orderedColors.at(4);

	std::pair<Color, std::vector<Color>>  finalFaceInfo;
	finalFaceInfo.first = faceColor;
	finalFaceInfo.second = orderedColors;

	return finalFaceInfo;

}


std::map<Color, std::vector<Color>> OrderSquares::getColorsInOrderForTwoFaces(std::vector<std::pair<MyPoint, Color>> initialOrder) {
	std::vector<std::pair<MyPoint, Color>> orderedByRows;
	std::vector<Color> orderedColorsForFirstFace;
	std::vector<Color> orderedColorsForSecondFace;

	sort(initialOrder.begin(), initialOrder.end(), sortbyrows);

	for (int k = 0; k < 3; k++) {

		orderedByRows.push_back(initialOrder.at(k * 3 + 0));
		orderedByRows.push_back(initialOrder.at(k * 3 + 1));
		orderedByRows.push_back(initialOrder.at(k * 3 + 2));

		sort(orderedByRows.begin(), orderedByRows.end(), sortbycols);
		for (int i = 0; i < orderedByRows.size(); i++) {
			orderedColorsForFirstFace.push_back(orderedByRows.at(i).second);
		}
		orderedByRows.clear();

	}

	for (int k = 3; k < 6; k++) {

		orderedByRows.push_back(initialOrder.at(k * 3 + 0));
		orderedByRows.push_back(initialOrder.at(k * 3 + 1));
		orderedByRows.push_back(initialOrder.at(k * 3 + 2));

		sort(orderedByRows.begin(), orderedByRows.end(), sortbycols);
		for (int i = 0; i < orderedByRows.size(); i++) {
			orderedColorsForSecondFace.push_back(orderedByRows.at(i).second);
		}
		orderedByRows.clear();

	}

	//identify the color of the face as it is the same with color of the square in the center
	Color firstFaceColor = orderedColorsForFirstFace.at(4);
	Color secondFaceColor = orderedColorsForSecondFace.at(4);

	std::map<Color, std::vector<Color>> facesInfo;
	facesInfo.insert({ firstFaceColor, orderedColorsForFirstFace });
	facesInfo.insert({ secondFaceColor, orderedColorsForSecondFace });

	return facesInfo;

}