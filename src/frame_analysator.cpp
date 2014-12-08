/*
 * frame_analysator.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#include <opencv2/core/core.hpp>

#include "frame_analysator.h"
#include "windows.h"

FrameAnalysator::FrameAnalysator(FrameWindow* frameWindow) :
	QueueHolder(deletePacketFreeFunc)
{
	this->frameWindow = frameWindow;
	activeRound = NULL;
	lastRound = NULL;
	activeStatistic = NULL;

	thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &FrameAnalysator::threadFunc));
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

		// show Frame
		if (img != NULL)
		{
			cv::Ptr<cv::Mat> sharedImg(img);
			frameWindow->notifyNewFrame(sharedImg);
		}
	}
}

void FrameAnalysator::startNewRound()
{
	// todo
}

