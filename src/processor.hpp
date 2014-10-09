/*
 * processor.h
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/thread.hpp>
#include <vector>

using namespace cv;


class FilterProcessor {
	std::vector<void(*)(Mat&)> *filters;
public:
	Mat image;
	FilterProcessor();
	~FilterProcessor();
	void addFilter(void(*)(Mat&));
	void process();
};


class PipelineProcessor {
	std::vector<FilterProcessor*> *filterProcessors;
public:
	PipelineProcessor();
	void addFilterProcessor(FilterProcessor*);
	void process();
	Mat join();
};

#endif /* PROCESSOR_HPP_ */
