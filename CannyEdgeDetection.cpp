#include "stdafx.h"
#include "CannyEdgeDetection.h"


CannyEdgeDetection::sobel_result CannyEdgeDetection::gradientSobel(Mat src) {

	int height = src.rows;
	int width = src.cols;

	Mat_<float> direction(height, width);
	Mat_<uchar> dst(height, width);
	Mat_<float> magnitude(height, width);

	int Sx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int Sy[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			int valX = 0;
			int valY = 0;

			for (int k = 0; k < 3; k++) {
				for (int p = 0; p < 3; p++) {

					valX += src.at<uchar>(i - 3 / 2 + k, j - 3 / 2 + p) * Sx[k][p];
					valY += src.at<uchar>(i - 3 / 2 + k, j - 3 / 2 + p) * Sy[k][p];

				}
			}

			float G = sqrt(valX * valX + valY * valY);
			G /= 4 * sqrt(2);

			dst(i, j) = (int)G;


			magnitude(i, j) = G;
			direction(i, j) = atan2(valY, valX);
		}
	}

	sobel_result res;
	res.mag = magnitude;
	res.dir = direction;
	res.res = dst;
	return res;
}

void CannyEdgeDetection::callGradientConvo() {
	char fname[MAX_PATH];

	while (openFileDlg(fname))
	{
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		gradientSobel(src);
	}
}

int CannyEdgeDetection::nonMaximaSuppression(float dir) {

	float pi = CV_PI;

	if ((dir >= pi / 8 && dir <= 3 * pi / 8) || (dir >= -7 * pi / 8 && dir <= -5 * pi / 8)) {
		return 1;
	}
	else if ((dir >= 3 * pi / 8 && dir <= 5 * pi / 8) || (dir >= -5 * pi / 8 && dir <= -3 * pi / 8)) {
		return 2;
	}
	else if ((dir >= 5 * pi / 8 && dir <= 7 * pi / 8) || (dir >= -3 * pi / 8 && dir <= -pi / 8)) {
		return 3;
	}
	else return 0;
}

Mat CannyEdgeDetection::applyNonMaximaSuppression(Mat src, Mat_<float> direction, Mat_<float> magnitude) {

	int height = src.rows;
	int width = src.cols;

	Mat_<uchar> dst(height, width);

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {

			int partition = nonMaximaSuppression(direction.at<float>(i, j));

			float pixel = magnitude.at<float>(i, j);

			int x1 = 0;
			int x2 = 0;
			int y1 = 0;
			int y2 = 0;

			switch (partition) {

			case 0:
				x1 = i;
				x2 = i;
				y1 = j - 1;
				y2 = j + 1;
				break;

			case 1:
				x1 = i + 1;
				x2 = i + 1;
				y1 = j - 1;
				y2 = j - 1;
				break;

			case 2:
				x1 = i + 1;
				x2 = i + 1;
				y1 = j;
				y2 = j;
				break;

			case 3:
				x1 = i - 1;
				x2 = i + 1;
				y1 = j - 1;
				y2 = j + 1;
				break;
			}

			float neigh1 = magnitude.at<float>(x1, y1);
			float neigh2 = magnitude.at<float>(x2, y2);

			if (!(pixel > neigh1 && pixel > neigh2)) {
				src.at<uchar>(i, j) = 0;
			}
		}
	}

	return src;
}

Mat CannyEdgeDetection::callBFSForCanny(Mat src, int threshold_low, int threshold_high) {

	// define neighbors
	int di[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dj[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int height = src.rows;
	int width = src.cols;

	int label = 0;
	Mat labels = Mat(height, width, CV_16SC1);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			labels.at<short>(i, j) = 0;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (src.at<uchar>(i, j) > threshold_high && labels.at<short>(i, j) == 0) {
				labels.at<short>(i, j) = 1;
				std::queue<Point2i> Q;
				Q.push({ j,i }); //j,i?
				while (!Q.empty()) {
					Point2i q = Q.front();
					Q.pop();
					for (int k = 0; k < 8; k++) {
						Point2i neighborPoint = { q.x + di[k], q.y + dj[k] };
						if (helperFunctions.isInsideImg(height, width, neighborPoint.y, neighborPoint.x)) {
							int neighbor = src.at<uchar>(neighborPoint);
							if (neighbor >= threshold_low && neighbor <= threshold_high && labels.at<short>(neighborPoint) == 0) {
								labels.at<short>(neighborPoint) = 1;
								Q.push(neighborPoint);
								//src.at<uchar>(neighborPoint) = 0;
							}
						}
					}
				}
			}
		}
	}

	Mat finalImg = Mat(height, width, CV_8UC1);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (labels.at<short>(i, j) == 1) {
				finalImg.at<uchar>(i, j) = 255;
			}
			else {
				finalImg.at<uchar>(i, j) = 0;
			}

		}
	}

	return finalImg;
}

Mat CannyEdgeDetection::callCannyEdgeDetection(Mat src, bool showProgression) {


	int height = src.rows;
	int width = src.cols;

	sobel_result step2_res = gradientSobel(src);


	//apply non maxima suppresion
	Mat step3_res = applyNonMaximaSuppression(step2_res.res, step2_res.dir, step2_res.mag);

	//adaptive thresholding
	int* hist = new int[256]();
	helperFunctions.computeHistogram(step3_res, hist);
	double p = 0.2;
	int NoNonEdge = (1 - p) * (height * width - hist[0]);
	int sum = 0;
	int adaptive_threshold = 0;
	for (int i = 1; i < 256; i++) {
		sum += hist[i];
		adaptive_threshold = i;
		if (sum > NoNonEdge) {
			break;
		}
	}

	int threshold_high = adaptive_threshold;
	double k = 0.3;
	int threshold_low = threshold_high * k;


	Mat finalImg = callBFSForCanny(step2_res.res, threshold_low, threshold_high);

	//apply dilation to enlarge edges
	Mat dilated = morphologicalOperations.applyDilation(finalImg);

	if (showProgression) {
		imshow("dilated", dilated);
		waitKey(0);
	}

	return dilated;
}


Mat CannyEdgeDetection::applyFilterToImg(Mat src, Mat filter, bool showProgression) {
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (filter.at<uchar>(i, j) == 255) {
				src.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
	if (showProgression) {
		imshow("applied filter", src);
		waitKey(0);
	}

	return src;
}

