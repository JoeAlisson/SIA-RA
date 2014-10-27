/*
 * filters.h
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#ifndef FILTERS_HPP_
#define FILTERS_HPP_

#include "processor.hpp"

void edgeDetectCanny(Mat&);

void edgeDetectSobel(Mat& img);

void edgeDetectLaplacian(Mat& img);

void Gaussian(Mat&);
void GaussianSatured(Mat&);


#endif /* FILTERS_HPP_ */
