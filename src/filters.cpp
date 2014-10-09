/*
 * filters.cpp
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#include "filters.hpp"

double dilation_size = 1.2;

void detectarBordas(Mat& img) {
    cvtColor(img, img, CV_BGR2GRAY);
    //bilateralFilter (frame, dst, 15, 80, 80 );
    GaussianBlur(img, img, Size(5,5), 5, 7);
    Canny(img, img, 0, 19,3);
    /// Apply the dilation operation
    dilate(img, img, getStructuringElement(MORPH_ELLIPSE, Size(2*dilation_size + 1, 2*dilation_size+1), Point(dilation_size, dilation_size)));
    bitwise_not(img,img);
    cvtColor(img, img, CV_GRAY2BGR);
}


void borrarFundo(Mat& frame) {
	GaussianBlur(frame, frame, Size(11,11), 9, 9);
}


