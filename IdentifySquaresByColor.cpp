#include "stdafx.h"
#include "IdentifySquaresByColor.h"


void IdentifySquaresByColor::identifyRubikCubeSquaresByColorsWithHSV(HsvMat hsvMat, Mat img) {

	//not utilized

	int height = img.rows;
	int width = img.cols;

	Mat yellowFromImg = Mat(height, width, CV_8UC3);
	Mat redFromImg = Mat(height, width, CV_8UC3);
	Mat greenFromImg = Mat(height, width, CV_8UC3);
	Mat whiteFromImg = Mat(height, width, CV_8UC3);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float H = (float)hsvMat.hue.at<uchar>(i, j);
			float S = (float)hsvMat.saturation.at<uchar>(i, j);
			H = H * 360 / 255;
			S = S / 255;

			if ((H > 40 && H < 70) && (S > 0.60) && (S <= 1.0)) {
				yellowFromImg.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
			}
			else {
				yellowFromImg.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}

			if (((H > 330 && H < 360) || (H > 0 && H < 15)) && (S > 0.60) && (S <= 1.0)) {
				redFromImg.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
			}
			else {
				redFromImg.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}

			if ((H > 80 && H < 150) && (S > 0.60) && (S <= 1.0)) {
				greenFromImg.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
			}
			else {
				greenFromImg.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}

			if (S <= 0.05) {
				whiteFromImg.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
			}
			else {
				whiteFromImg.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}

		}
	}


	imshow("yellow from image", yellowFromImg);
	imshow("red from image", redFromImg);
	imshow("green from image", greenFromImg);
	imshow("white from image", whiteFromImg);
	waitKey(0);

}

std::string identifyColor(Color color) {
	switch (color) {
	case red: return "red";
	case orange: return "orange";
	case blue: return "blue";
	case green: return "green";
	case white: return "white";
	case yellow: return "yellow";
	}
}


std::map<Color, Mat> IdentifySquaresByColor::identifyRubikCubeSquaresByColorsWithYuv(YuvMat yuvMat, Mat img, bool showProgress) {

	int height = img.rows;
	int width = img.cols;
	Mat yellowFromImg = Mat(height, width, CV_8UC3);
	Mat redFromImg = Mat(height, width, CV_8UC3);
	Mat greenFromImg = Mat(height, width, CV_8UC3);
	Mat whiteFromImg = Mat(height, width, CV_8UC3);
	Mat blueFromImg = Mat(height, width, CV_8UC3);
	Mat orangeFromImg = Mat(height, width, CV_8UC3);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float Y = (float)yuvMat.Y.at<uchar>(i, j);
			float Up = (float)yuvMat.Up.at<uchar>(i, j);
			float Vp = (float)yuvMat.Vp.at<uchar>(i, j);

			//modified values 
			redFromImg.at<Vec3b>(i, j) = ((Y > 50 && Y < 150) && (Up > 70 && Up < 148) && (Vp > 170 && Vp < 250)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
			orangeFromImg.at<Vec3b>(i, j) = ((Y > 79 && Y < 210) && (Up >= 17 && Up < 95) && (Vp > 160 && Vp < 195)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
			blueFromImg.at<Vec3b>(i, j) = ((Y > 20 && Y < 240) && (Up > 155 && Up < 250) && (Vp > 0 && Vp < 110)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
			greenFromImg.at<Vec3b>(i, j) = ((Y > 30 && Y < 240) && (Up > 5 && Up < 135) && (Vp > 10 && Vp < 110)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
			whiteFromImg.at<Vec3b>(i, j) = ((Y > 130 && Y < 255) && (Up > 105 && Up < 155) && (Vp > 85 && Vp < 145)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
			yellowFromImg.at<Vec3b>(i, j) = ((Y > 105 && Y < 255) && (Up >= 0 && Up < 100) && (Vp > 115 && Vp < 150)) ? img.at<Vec3b>(i, j) : Vec3b(0, 0, 0);
		}
	}

	std::map<Color, Mat> squaresByColor = { {red, redFromImg,},
							   {orange, orangeFromImg,},
							   {blue, blueFromImg,},
							   {green, greenFromImg,},
							   {white, whiteFromImg,},
							   {yellow, yellowFromImg,} };

	for (auto& squareGroup : squaresByColor) {
		if (showProgress) {
			imshow("before erosion" + identifyColor(squareGroup.first), squareGroup.second);
		}

		//apply erosion to eliminate the groups of pixels that are too small to be a square 
		Mat ero = morphologicalOperations.applyErosion(
			imageColorTransformations.convertToBinary(imageColorTransformations.rgbToGrayscaleImage(squareGroup.second)));
		for (int i = 0; i < 4; i++) {
			ero = morphologicalOperations.applyErosion(ero);
		}

		for (int i = 0; i < 2; i++) {
			ero = morphologicalOperations.applyDilation(ero);
		}
		
		squareGroup.second = ero;

		if (showProgress) {
			imshow("after erosion " + identifyColor(squareGroup.first), squareGroup.second);
			waitKey(0);
		}
	}

	return squaresByColor;
}
