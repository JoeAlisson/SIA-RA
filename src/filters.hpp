/*
 * filters.h
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#ifndef FILTERS_HPP_
#define FILTERS_HPP_

#include "processor.hpp"
#include <opencv2/photo/photo.hpp>
#include <opencv2/objdetect/objdetect.hpp>

void edgeDetectCanny(Mat&);
void edgeDetectSobel(Mat& img);
void edgeDetectLaplacian(Mat& img);

void edgeDetect(Mat& img);



void Gaussian(Mat&);
void GaussianSatured(Mat&);
void bilateralSatured(Mat&);


#endif /* FILTERS_HPP_ */
