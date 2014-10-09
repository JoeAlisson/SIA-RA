/*
 * processor.cpp
 *
 *  Created on: 08/10/2014
 *      Author: Alisson Oliveira
 */

#include "processor.hpp"

using namespace std;


//  Implementação FilterProcessor
FilterProcessor::FilterProcessor() {
	filters = new std::vector<void(*)(Mat&)>();
}

FilterProcessor::~FilterProcessor() {
	delete filters;
}

void FilterProcessor::addFilter(void (*filter)(Mat&)) {
	filters->push_back(filter);
}

void FilterProcessor::process() {
	for (unsigned short i = 0; i < filters->size(); i++) {
		filters->at(i)(image);
	}
}

// Implementação PipelineProcessor
PipelineProcessor::PipelineProcessor() {
	filterProcessors = new std::vector<FilterProcessor*>();
}

void PipelineProcessor::addFilterProcessor(FilterProcessor* fProcessor) {
	filterProcessors->push_back(fProcessor);
}

void PipelineProcessor::process() {
	boost::thread_group thr;
	for (unsigned short i = 0; i < filterProcessors->size(); i++) {
		thr.create_thread(boost::bind(&FilterProcessor::process, filterProcessors->at(i)));
	}
	thr.join_all();
}

Mat PipelineProcessor::join() {
	Mat result;
	filterProcessors->at(0)->image.copyTo(result);
	unsigned short len = filterProcessors->size() - 1;
	for (unsigned short i = 0; i < len; i++) {
		bitwise_and(result,filterProcessors->at(i+1)->image, result);
	}

	return result;
}
