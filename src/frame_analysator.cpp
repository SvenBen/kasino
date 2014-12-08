/*
 * frame_analysator.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#include <opencv2/core/core.hpp>

#include "frame_analysator.h"

FrameAnalysator::FrameAnalysator() :
	QueueHolder(deletePacketFreeFunc)
{
	activeRound = NULL;
	activeStatistic = NULL;
	// TODO Auto-generated constructor stub

}

FrameAnalysator::~FrameAnalysator()
{
	quit = true;
	if (thread != NULL)
	{
		thread->join();
	}
	// TODO
}

void FrameAnalysator::threadFunc()
{
	while (!quit)
	{
		cv::Mat* img = timeout_pop();
		delete img;
		// todo
	}
}

void FrameAnalysator::startNewRound()
{
	// todo
}

