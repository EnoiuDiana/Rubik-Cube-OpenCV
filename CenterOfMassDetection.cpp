#include "stdafx.h"
#include "CenterOfMassDetection.h"


std::vector<MyPoint> CenterOfMassDetection::callBFSToFindCenterOfMass(Mat src, bool showProgress) {

	std::vector<MyPoint> centerOfMassPoints;

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
			if (src.at<uchar>(i, j) == 255 && labels.at<short>(i, j) == 0) {
				label++;
				labels.at<short>(i, j) = label;
				std::queue<Point2i> Q;
				Q.push({ j,i }); //j,i?
				while (!Q.empty()) {
					Point2i q = Q.front();
					Q.pop();
					for (int k = 0; k < 8; k++) {
						Point2i neighborPoint = { q.x + di[k], q.y + dj[k] };
						if (helperFunctions.isInsideImg(height, width, neighborPoint.y, neighborPoint.x)) {
							int neighbor = src.at<uchar>(neighborPoint);
							if (neighbor == 255 && labels.at<short>(neighborPoint) == 0) {
								labels.at<short>(neighborPoint) = label;
								Q.push(neighborPoint);
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
			finalImg.at<uchar>(i, j) = 0;

		}
	}

	//get center of mass for each component
	for (int l = 1; l <= label; l++) {
		int area = 0;
		int ri = 0;
		int ci = 0;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (labels.at<short>(i, j) == l) {
					finalImg.at<uchar>(i, j) = 255;
					//area
					area++;
					//center of mass
					ri += i;
					ci += j;
				}
			}
		}

		//calcultae center of mass
		ri = ri / area;
		ci = ci / area;

		finalImg.at <uchar>(ri, ci) = 0;

		centerOfMassPoints.push_back(helperFunctions.initPoint(ri, ci));
	}

	if (showProgress) {
		imshow("center of mass points", finalImg);
		waitKey(0);
	}

	return centerOfMassPoints;
}

