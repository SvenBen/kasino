/*
 * frame_analysator.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "frame_analysator.h"
#include "windows.h"
#include "frame.h"
#include "statistic.h"

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
		Frame* orgFrame = timeout_pop();
		if (orgFrame != NULL)
		{
			if (frameWindow->getVisible())
			{
				// This frame is for all manipulations
				Frame manipulatedFrameBGR(*orgFrame);
				manipulatedFrameBGR.mat = manipulatedFrameBGR.mat.clone();


				// todo manipulate here


				// Create a shared Frame in RGB
				boost::shared_ptr<Frame> manipulatedFrameRGB(new Frame(manipulatedFrameBGR));
				cv::cvtColor(manipulatedFrameRGB->mat, manipulatedFrameRGB->mat, CV_BGR2RGB);

				frameWindow->notifyNewFrame(manipulatedFrameRGB);
			}
		}
	}
}

void FrameAnalysator::startNewRound()
{
	// todo
}

