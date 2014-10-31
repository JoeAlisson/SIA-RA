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

class PipelineProcessor;

class FilterProcessor {
	std::vector<void(*)(Mat&)> *filters;
	Mat image;
	friend class PipelineProcessor;
public:
	FilterProcessor();
	~FilterProcessor();
	void addFilter(void(*)(Mat&));
	void process();
	const Mat& getImage() const;
};


class PipelineProcessor {
	std::vector<FilterProcessor*> *filterProcessors;
	int pyramid;
public:
	PipelineProcessor();
	~PipelineProcessor();
	void addFilterProcessor(FilterProcessor*);
	void setPyramid(int);
	void setImage(Mat&);
	void process();
	Mat join();
};

#endif /* PROCESSOR_HPP_ */
