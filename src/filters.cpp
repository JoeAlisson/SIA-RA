/*
 * filters.cpp
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#include "filters.hpp"

double dilation_size = 1.5;

void edgeDetectCanny(Mat& img) {
	cvtColor(img, img, CV_BGR2GRAY);
	GaussianBlur(img, img, Size(7, 7), 2, 2);
	Canny(img, img, 0, 22, 3, true);
	dilate(img, img, getStructuringElement(MORPH_ELLIPSE, Size(1.5 * dilation_size + 1, 1.5 * dilation_size + 1), Point(dilation_size, dilation_size)));
	bitwise_not(img, img);
	cvtColor(img, img, CV_GRAY2BGR);
}

void edgeDetectSobel(Mat& img) {
	Mat gray, temp;
	GaussianBlur(img, img, Size(7, 7), 0.3, 0.3);
	cvtColor(img, gray, CV_RGB2GRAY);
	//x
	Sobel(gray, img, CV_16S, 1, 0, 3, 2.5, 1.3, BORDER_DEFAULT);

	convertScaleAbs(img, img);
	//y
	Sobel(gray, temp, CV_16S, 0, 1, 3, 2.5, 1.3, BORDER_DEFAULT);

	convertScaleAbs(temp, temp);
	addWeighted(img, 0, temp, 0.3, 1, img);
	threshold(img, img, 15, 255, THRESH_BINARY_INV);
	cvtColor(img, img, CV_GRAY2BGR);

}

void edgeDetectLaplacian(Mat& img) {
	GaussianBlur(img, img, Size(5, 5), 0, 0);
	cvtColor(img, img, CV_RGB2GRAY);
	Laplacian( img, img, CV_16S, 3, 1, 0, BORDER_DEFAULT );
	threshold(img, img, 6, 255, THRESH_BINARY_INV);
	convertScaleAbs( img, img );
	cvtColor(img, img, CV_GRAY2BGR);
}

void saturarHSI(Mat& src, Mat& dst, int value) {
	vector<Mat> hsv_planes;
	split(src, hsv_planes);
	hsv_planes[1] = hsv_planes[1] + value;
	merge(hsv_planes, dst);
}

void saturar(Mat& src, Mat& dst, int value) {
	Mat tmp;
	cvtColor(src, tmp, CV_BGR2HSV);
	saturarHSI(tmp, dst, value);
	cvtColor(dst, dst, CV_HSV2BGR);
}

void GaussianSatured(Mat& frame) {
	medianBlur(frame,frame,3);
	saturar(frame,frame,55);
	GaussianBlur(frame, frame, Size(13, 13), 5, 5);

}
void Gaussian(Mat& frame) {
	GaussianBlur(frame, frame, Size(11, 11), 7, 7);

}
