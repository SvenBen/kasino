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
#include "macros.h"
#include "image_saver.h"

FrameAnalysator::FrameAnalysator(FrameWindow* frameWindow) :
	QueueHolder(deletePacketFreeFunc)
{
	this->frameWindow = frameWindow;
	imgSaverQueueUser = NULL;
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

	createFramesForImgSaver(false);
	// TODO
}

void FrameAnalysator::createFramesForImgSaver(bool onOff, ImageSaver* imgSaver)
{
	if (onOff)
	{
		assert(imgSaver != NULL);
		imgSaverQueueUser = new QueueUser<Frame*>(imgSaver);
	}
	else
	{
		SAFE_DELETE_NULL(imgSaverQueueUser)
	}
}

void FrameAnalysator::threadFunc()
{
	while (!quit)
	{
		Frame* orgFrame = timeout_pop();
		if (orgFrame != NULL)
		{
			if (frameWindow->getVisible() || imgSaverQueueUser != NULL)
			{
				// This frame is for all manipulations
				Frame manipulatedFrameBGR(*orgFrame);
				manipulatedFrameBGR.mat = manipulatedFrameBGR.mat.clone();


				// todo manipulate here


				// Create a shared Frame in RGB
				Frame* manipulatedFrameRGB = new Frame(manipulatedFrameBGR);
				manipulatedFrameRGB->mat = manipulatedFrameRGB->mat.clone();
				cv::cvtColor(manipulatedFrameBGR.mat, manipulatedFrameRGB->mat, CV_BGR2RGB);
				if (frameWindow->getVisible())
				{
					Frame* manipulatedFrameRGBcopy = new Frame(*manipulatedFrameRGB);
					manipulatedFrameRGBcopy->mat = manipulatedFrameRGBcopy->mat.clone();
					SharedFramePtr manipulatedFrameRGBShared(manipulatedFrameRGBcopy);
					frameWindow->notifyNewFrame(manipulatedFrameRGBShared);
				}

				if (imgSaverQueueUser != NULL)
				{
					imgSaverQueueUser->push(manipulatedFrameRGB);
				}
				else
				{
					delete manipulatedFrameRGB;
				}
			}
		}
	}
}

void FrameAnalysator::startNewRound()
{
	// todo
}

