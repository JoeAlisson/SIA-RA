#include "Kalman.h"

Kalman::Kalman(){
    float m[2][2] = {{1, 1}, {0, 1}};
	for(int i=0;i<4;i++){
		kalman_vector.push_back(KalmanFilter(2, 1, 0));
		measurement_vector.push_back(Mat(1, 1, CV_32FC1));
		state_vector.push_back(Mat(2, 1, CV_32FC1));
		measurement_noise.push_back(Mat(1, 1, CV_32FC1));
		process_noise.push_back(Mat(2, 1, CV_32FC1));

	    kalman_vector.at(i).transitionMatrix = Mat(2, 2, CV_32FC1, m);

		setIdentity(kalman_vector.at(i).measurementMatrix,Scalar(1));
		setIdentity(kalman_vector.at(i).processNoiseCov,  Scalar(1e-5));
		setIdentity(kalman_vector.at(i).measurementNoiseCov, Scalar(1e-1));
		setIdentity(kalman_vector.at(i).errorCovPost, Scalar(1));

        randu(state_vector.at(i), Scalar(0), Scalar(0.1));
        randu(kalman_vector.at(i).statePost, Scalar(0), Scalar(0.1));
        randn(measurement_noise.at(i), Scalar(0),Scalar(0.1,0.1));
        randn(process_noise.at(i), Scalar(0),Scalar(0.1,0.1));
        randn(measurement_noise.at(i), Scalar(0),Scalar(0.1,0.1));
	}
}
Marker Kalman::prever(Marker& marcador){
	for(int i=0;i<4;i++){
		state_vector.at(i).at<float>(0) = marcador.at(i).x;
		state_vector.at(i).at<float>(1) = marcador.at(i).y;

		kalman_vector.at(i).predict();

		measurement_vector.at(i) = kalman_vector.at(i).measurementMatrix
				                 * state_vector.at(i) + measurement_noise.at(i);

		kalman_vector.at(i).correct(measurement_vector.at(i));

		process_noise.at(i) = kalman_vector.at(i).processNoiseCov.at<float>(0,0);

        state_vector.at(i) = kalman_vector.at(i).transitionMatrix
        		* state_vector.at(i) + process_noise.at(i);

		marcador.at(i).x = state_vector.at(i).at<float>(0);
		marcador.at(i).y = state_vector.at(i).at<float>(1);
	}

	 return marcador;
}
