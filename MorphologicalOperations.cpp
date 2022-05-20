#include "stdafx.h"
#include "MorphologicalOperations.h"

std::vector<std::pair<int, int>> MorphologicalOperations::getStructuringElement() {

	std::vector<std::pair<int, int>> structElem;
	structElem.push_back(std::pair<int, int>(0, -1));
	structElem.push_back(std::pair<int, int>(-1, 0));
	structElem.push_back(std::pair<int, int>(0, 1));
	structElem.push_back(std::pair<int, int>(1, 0));

	return structElem;
}

Mat MorphologicalOperations::applyDilation(Mat src) {
	int height = src.rows;
	int width = src.cols;

	int black = 0;
	int white = 255;

	Mat dst = Mat(height, width, CV_8UC1);
	std::vector<std::pair<int, int>> structElem = getStructuringElement();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (src.at<uchar>(i, j) == white) {
				for (int k = 0; k < 4; k++) {
					int x_coord = i + structElem[k].first;
					int y_coord = j + structElem[k].second;
					if (helperFunctions.isInsideImg(height, width, x_coord, y_coord)) {
						dst.at<uchar>(x_coord, y_coord) = white;
					}
				}
			}
		}
	}
	return dst;

}

Mat MorphologicalOperations::applyErosion(Mat src) {
	int height = src.rows;
	int width = src.cols;

	int black = 0;
	int white = 255;

	Mat dst = Mat(height, width, CV_8UC1);
	std::vector<std::pair<int, int>> structElem = getStructuringElement();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst.at<uchar>(i, j) = black;
		}
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (src.at<uchar>(i, j) == white) {
				int containedParts = 0;
				for (int k = 0; k < 4; k++) {
					int x_coord = i + structElem[k].first;
					int y_coord = j + structElem[k].second;
					if (helperFunctions.isInsideImg(height, width, x_coord, y_coord) && src.at<uchar>(x_coord, y_coord) == white) {
						containedParts++;
					}
				}
				if (containedParts == 4) {
					dst.at<uchar>(i, j) = src.at<uchar>(i, j);
				}
			}
		}
	}
	return dst;
}
