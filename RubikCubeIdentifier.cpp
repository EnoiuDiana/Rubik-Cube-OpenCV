#include "stdafx.h"
#include "RubikCubeIdentifier.h"


void RubikCubeIdentifier::callRubikCubeIdentifierUsingOneFace() {

	char fname[MAX_PATH];
	std::vector<Mat> faces;
	std::vector<Mat> faces_grayscale;
	for (int i = 0; i < 6; i++) {
		openFileDlg(fname);
		Mat currentFaceRead = imread(fname);
		Mat currentFaceRead2 = imread(fname, IMREAD_GRAYSCALE);
		faces.push_back(currentFaceRead);
		faces_grayscale.push_back(currentFaceRead2);
	}

	std::map<Color, std::vector<Color>> facesInfo;

	bool showProgress = true;

	for (int i = 0; i < 6; i++) {

		printf("Identifying face %d ...\n", i);

		// amplify edges
		Mat filter = cannyEdgeDetection.callCannyEdgeDetection(faces_grayscale.at(i), showProgress);
		cannyEdgeDetection.applyFilterToImg(faces.at(i), filter, showProgress);

		struct YuvMat yuvMat = imageColorTransformations.rgbToYuvConversion(faces.at(i));

		if (showProgress) {
			imshow("Y", yuvMat.Y);
			imshow("U", yuvMat.Up);
			imshow("V", yuvMat.Vp);
			waitKey(0);
		}

		std::map<Color, Mat> squaresByColor = identifySquaresByColor.identifyRubikCubeSquaresByColorsWithYuv(yuvMat, faces.at(i), showProgress);

		std::vector<std::pair<MyPoint, Color>> listOfSquaresByCenterOfMassAndColor;

		std::vector<Color> colors = { red, orange, blue, green, white, yellow };

		for (Color color : colors) {
			std::vector<MyPoint> listOfCenterOfMassPoints = centerOfMassDetection.callBFSToFindCenterOfMass(squaresByColor[color], showProgress);

			for (int i = 0; i < listOfCenterOfMassPoints.size(); i++) {
				listOfSquaresByCenterOfMassAndColor.push_back(std::pair<MyPoint, Color>(listOfCenterOfMassPoints.at(i), color));
			}
		}

		if (listOfSquaresByCenterOfMassAndColor.size() != 9) {
			printf("Sometimg went wrong..\n");
			exit(1);
		}

		std::pair<Color, std::vector<Color>> faceInfo = orderSquares.getColorsInOrderForOneFace(listOfSquaresByCenterOfMassAndColor);
		facesInfo.insert({ faceInfo.first, faceInfo.second });

		if (showProgress) {
			Mat_<Vec3b> result(300, 300);
			projectRubikCube.projectFace(result, 23, 23, faceInfo.second, faceInfo.first);
			imshow("Final face", result);
			waitKey(0);
		}

		showProgress = false;
	}

	projectRubikCube.projectRubikCube(facesInfo);

}

void RubikCubeIdentifier::callRubikCubeIdentifierUsingTwoFaces() {

	char fname[MAX_PATH];
	std::vector<Mat> faces;
	std::vector<Mat> faces_grayscale;
	for (int i = 0; i < 3; i++) {
		openFileDlg(fname);
		Mat currentFaceRead = imread(fname);
		Mat currentFaceRead2 = imread(fname, IMREAD_GRAYSCALE);
		faces.push_back(currentFaceRead);
		faces_grayscale.push_back(currentFaceRead2);
	}

	std::map<Color, std::vector<Color>> facesInfo;

	bool showProgress = true;

	for (int i = 0; i < 3; i++) {

		printf("Identifying face %d ...\n", i);

		// amplify edges
		Mat filter = cannyEdgeDetection.callCannyEdgeDetection(faces_grayscale.at(i), showProgress);
		cannyEdgeDetection.applyFilterToImg(faces.at(i), filter, showProgress);

		struct YuvMat yuvMat = imageColorTransformations.rgbToYuvConversion(faces.at(i));

		if (showProgress) {
			imshow("Y", yuvMat.Y);
			imshow("U", yuvMat.Up);
			imshow("V", yuvMat.Vp);
			waitKey(0);
		}

		std::map<Color, Mat> squaresByColor = identifySquaresByColor.identifyRubikCubeSquaresByColorsWithYuv(yuvMat, faces.at(i), showProgress);

		std::vector<std::pair<MyPoint, Color>> listOfSquaresByCenterOfMassAndColor;

		std::vector<Color> colors = { red, orange, blue, green, white, yellow };

		for (Color color : colors) {
			std::vector<MyPoint> listOfCenterOfMassPoints = centerOfMassDetection.callBFSToFindCenterOfMass(squaresByColor[color], showProgress);

			for (int i = 0; i < listOfCenterOfMassPoints.size(); i++) {
				listOfSquaresByCenterOfMassAndColor.push_back(std::pair<MyPoint, Color>(listOfCenterOfMassPoints.at(i), color));
			}
		}

		if (listOfSquaresByCenterOfMassAndColor.size() != 18) {
			printf("Sometimg went wrong..\n");
			exit(1);
		}


		std::map<Color, std::vector<Color>> twoFacesInfo = orderSquares.getColorsInOrderForTwoFaces(listOfSquaresByCenterOfMassAndColor);
		for (auto& faceInfo : twoFacesInfo) {
			facesInfo.insert({ faceInfo.first, faceInfo.second });

			if (showProgress) {
				Mat_<Vec3b> result(300, 300);
				projectRubikCube.projectFace(result, 23, 23, faceInfo.second, faceInfo.first);
				imshow("Final face ", result);
				waitKey(0);
			}
		}

		showProgress = false;
	}

	projectRubikCube.projectRubikCube(facesInfo);

}

void RubikCubeIdentifier::identifySpectrumOfColors() {

	char fname[MAX_PATH];
	openFileDlg(fname);
	Mat currentFaceRead = imread(fname);
	struct YuvMat yuvMat = imageColorTransformations.rgbToYuvConversion(currentFaceRead);
	std::map<Color, Mat> squaresByColor = identifySquaresByColor.identifyRubikCubeSquaresByColorsWithYuv(yuvMat, currentFaceRead, true);

}