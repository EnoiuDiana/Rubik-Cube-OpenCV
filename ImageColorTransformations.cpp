#include "stdafx.h"
#include "ImageColorTransformations.h"


Mat ImageColorTransformations::rgbToGrayscaleImage(Mat img) {

	int height = img.rows;
	int width = img.cols;

	Mat greyscaleImg = Mat(height, width, CV_8UC1);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			Vec3b pixel = img.at<Vec3b>(i, j);
			uchar meanValue = (pixel[0] + pixel[1] + pixel[2]) / 3;
			greyscaleImg.at<uchar>(i, j) = meanValue;

		}
	}
	return greyscaleImg;
}

Mat ImageColorTransformations::convertToBinary(Mat img) {
	int height = img.rows;
	int width = img.cols;
	Mat binaryImg = Mat(height, width, CV_8UC1);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			uchar pixel = img.at<uchar>(i, j);
			if (pixel != 0) {
				binaryImg.at<uchar>(i, j) = 255;
			}
			else {
				binaryImg.at<uchar>(i, j) = 0;
			}
		}
	}
	return binaryImg;
}


HsvMat ImageColorTransformations::rgbToHsvConversion(Mat img) {

	int height = img.rows;
	int width = img.cols;

	Mat hueImg = Mat(height, width, CV_8UC1);
	Mat saturationImg = Mat(height, width, CV_8UC1);
	Mat valueImg = Mat(height, width, CV_8UC1);

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			Vec3b pixel = img.at<Vec3b>(i, j);

			float r = (float)pixel[2] / 255;
			float g = (float)pixel[1] / 255;
			float b = (float)pixel[0] / 255;

			float M = helperFunctions.computeMaxValue(r, g, b);
			float m = helperFunctions.computeMinValue(r, g, b);
			float C = M - m;

			//value
			float V = M;

			//saturation
			float S = 0;
			if (V != 0) {
				S = C / V;
			}

			//hue
			float H = 0;
			if (C != 0) {
				if (M == r) {
					H = 60 * (g - b) / C;
				}
				if (M == g) {
					H = 120 + 60 * (b - r) / C;
				}
				if (M == b) {
					H = 240 + 60 * (r - g) / C;
				}
			}

			if (H < 0) {
				H += 360;
			}

			hueImg.at<uchar>(i, j) = H * 255 / 360;
			saturationImg.at<uchar>(i, j) = S * 255;
			valueImg.at<uchar>(i, j) = V * 255;

		}
	}

	struct HsvMat hsvMat;
	hsvMat.value = valueImg;
	hsvMat.saturation = saturationImg;
	hsvMat.hue = hueImg;

	return hsvMat;

}



YuvMat ImageColorTransformations::rgbToYuvConversion(Mat img) {

	int height = img.rows;
	int width = img.cols;

	Mat YImg = Mat(height, width, CV_8UC1);
	Mat UpImg = Mat(height, width, CV_8UC1);
	Mat VpImg = Mat(height, width, CV_8UC1);

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			Vec3b pixel = img.at<Vec3b>(i, j);

			int R = pixel[2];
			int G = pixel[1];
			int B = pixel[0];

			float Y = R * .299000 + G * .587000 + B * .114000;
			float U = R * -.168736 + G * -.331264 + B * .500000 + 128;
			float V = R * .500000 + G * -.418688 + B * -.081312 + 128;

			float Y_prime = 255.0f;

			float k = 1.0f;

			if (Y > 128) {
				k = (float)Y_prime / Y;
			}
			else if (Y < 128) {
				k = (float)(256 - Y) / Y_prime;
			}

			YImg.at<uchar>(i, j) = Y;
			UpImg.at<uchar>(i, j) = U;
			VpImg.at<uchar>(i, j) = V;

		}
	}

	//imshow("Y", YImg);
	//imshow("Up", UpImg);
	//imshow("Vp", VpImg);
	//waitKey(0);

	struct YuvMat yuvMat;
	yuvMat.Y = YImg;
	yuvMat.Up = UpImg;
	yuvMat.Vp = VpImg;

	return yuvMat;

}
