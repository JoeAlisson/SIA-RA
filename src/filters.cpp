/*
 * filters.cpp
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#include "filters.hpp"

double dilation_size = 2;
String face_cascade_name = "lbpcascade_frontalface.xml";
CascadeClassifier face_cascade;
bool loaded = face_cascade.load(face_cascade_name);

void edgeDetect(Mat& img) {
	GaussianBlur(img, img, Size(3, 3), 0, 0);
	Mat tmp;
	img.copyTo(tmp);
	Canny(img, img, 30, 100, 3, true);
	bitwise_not(img, img);
	erode(img, img, getStructuringElement(MORPH_ELLIPSE, Size(dilation_size + 1, dilation_size + 1), Point(dilation_size, dilation_size)));

	if(loaded) {
		std::vector<Rect> faces;
		cvtColor(tmp, tmp, COLOR_BGR2GRAY );
		equalizeHist( tmp, tmp);
		face_cascade.detectMultiScale(tmp, faces, 1.1, 2, 0, Size(80, 80));

		for( size_t i = 0; i < faces.size(); i++ )  {
		        Mat faceROI = tmp(faces[i]);
		        Laplacian(faceROI, faceROI, CV_16S, 3, 2.5, 1, BORDER_DEFAULT);
		        threshold(faceROI, faceROI, 7, 255, THRESH_BINARY_INV);
		        convertScaleAbs(faceROI, faceROI);
		        dilate(faceROI, faceROI, getStructuringElement(MORPH_ELLIPSE, Size(2, 2), Point(1, 1)));
		        faceROI.copyTo(img(faces[i]));
		        rectangle(img, faces[i], Scalar( 255, 190, 0 ));

		    }
	}
	cvtColor(img, img, CV_GRAY2BGR);

}

void edgeDetectCanny(Mat& img) {
	//GaussianBlur(img, img, Size(5,5), 0, 0);
	bilateralSatured(img);
	Canny(img, img, 30, 100, 3, true);
	bitwise_not(img, img);
	erode(img, img, getStructuringElement(MORPH_ELLIPSE, Size(dilation_size + 1, dilation_size + 1), Point(dilation_size, dilation_size)));
	cvtColor(img, img, CV_GRAY2BGR);
}

/**
 * Efeito de pintura.
 */
void edgeDetectSobel(Mat& img) {
	Mat gray, temp;
	GaussianBlur(img, img, Size(3, 3), 0, 0);
	cvtColor(img, gray, CV_RGB2GRAY);
	//x
	Sobel(gray, img, CV_16S, 1, 0, 3, 1.5, 0.3, BORDER_DEFAULT);

	convertScaleAbs(img, img);
	//y
	Sobel(gray, temp, CV_16S, 0, 1, 3, 1.5, 0.4, BORDER_DEFAULT);

	convertScaleAbs(temp, temp);
	addWeighted(img, .3, temp, .3, .3, img);

	erode(img, img,
			getStructuringElement(MORPH_ELLIPSE,
					Size(dilation_size + 1, dilation_size + 1),
					Point(dilation_size, dilation_size)));
	bitwise_not(img, img);
	cvtColor(img, img, CV_GRAY2BGR);

}

void edgeDetectLaplacian(Mat& img) {
	GaussianBlur(img, img, Size(3, 3), 0, 0);
	cvtColor(img, img, CV_RGB2GRAY);
	Laplacian(img, img, CV_16S, 3, 2, 1, BORDER_DEFAULT);
	threshold(img, img, 7, 255, THRESH_BINARY_INV);
	convertScaleAbs(img, img);
	dilate(img, img,
			getStructuringElement(MORPH_ELLIPSE, Size(2, 2), Point(1, 1)));
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
	medianBlur(frame, frame, 3);
	saturar(frame, frame, 50);
	GaussianBlur(frame, frame, Size(13, 13), 5, 5);
}

void bilateral(Mat& frame) {
	Mat tmp;
	for (int i = 0; i < 2; ++i) {
		pyrDown(frame, frame, Size(frame.cols / 2, frame.rows / 2));
	}
	bilateralFilter(tmp, frame, 3, 3, 3);
	for (int i = 0; i < 2; ++i) {
		pyrUp(frame, frame, Size(frame.cols * 2, frame.rows * 2));
	}
}

void bilateralSatured(Mat& frame) {
	Mat tmp;
	for (int i = 0; i < 2; ++i) {
		pyrDown(frame, frame, Size(frame.cols / 2, frame.rows / 2));
	}
	saturar(frame, tmp, 55);
	bilateralFilter(tmp, frame, 3, 3, 3);
	for (int i = 0; i < 2; ++i) {
		pyrUp(frame, frame, Size(frame.cols * 2, frame.rows * 2));
	}
}
void Gaussian(Mat& frame) {
	GaussianBlur(frame, frame, Size(11, 11), 7, 7);

}
