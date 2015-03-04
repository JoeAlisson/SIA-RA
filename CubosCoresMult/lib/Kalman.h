/*
 * Kalman.h
 *
 *  Created on: 03/12/2014
 *      Author: pedro
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <aruco.h>
#include <vector>

using namespace cv;
using namespace aruco;

class Kalman{
private:
	vector<KalmanFilter> kalman_vector;
	vector<Mat_<float> > measurement_vector;
	vector<Mat_<float> > measurement_noise;
	vector<Mat> state_vector;
	vector<Mat> process_noise;
public:
	Kalman();
	Marker prever(Marker&);
};



#endif /* KALMAN_H_ */
