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
#include "video_writer.h"
#include "mat_manipulator.h"

FrameAnalysator::FrameAnalysator(FrameWindow* frameWindow, MainWindow* mainWindow) :
	QueueHolder(deleteFrameFreeFunc)
{
	this->frameWindow = frameWindow;
	this->mainWindow = mainWindow;
	imgSaverQueueUser = NULL;
	vidWriterQueueUser = NULL;
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
	createFramesForVidWriter(false);
}

void FrameAnalysator::createFramesForImgSaver(bool onOff, ImageSaver* imgSaver)
{
	Glib::Threads::Mutex::Lock lock(mutex);
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

void FrameAnalysator::createFramesForVidWriter(bool onOff, VideoWriter* vidWriter)
{
	Glib::Threads::Mutex::Lock lock(mutex);
	if (onOff)
	{
		assert(vidWriter != NULL);
		vidWriterQueueUser = new QueueUser<Frame*>(vidWriter);
	}
	else
	{
		SAFE_DELETE_NULL(vidWriterQueueUser)
	}
}

void FrameAnalysator::threadFunc()
{
	while (!quit)
	{
		Frame* orgFrame = timeout_pop();
		if (orgFrame != NULL)
		{
			orgFrame->timeSinceRoundStart = orgFrame->pts;

			if (frameWindow->getVisible() || imgSaverQueueUser != NULL || vidWriterQueueUser != NULL)
			{
				// frameBGR is for all manipulations
				Frame frameBGR(*orgFrame);
				frameBGR.mat = orgFrame->mat.clone();

				// Write and draw infos in Mat
				MatManipulator m(&frameBGR, mainWindow);
				m.drawInfos();

				// Create a shared Frame in RGB
				Frame* frameRGB = new Frame(frameBGR);
				frameRGB->mat = frameRGB->mat.clone();
				cv::cvtColor(frameBGR.mat, frameRGB->mat, CV_BGR2RGB);
				if (frameWindow->getVisible())
				{
					Frame* frameRGBcopy = new Frame(*frameRGB);
					frameRGBcopy->mat = frameRGBcopy->mat.clone();
					SharedFramePtr frameRGBShared(frameRGBcopy);
					frameWindow->notifyNewFrame(frameRGBShared);
				}

				if (vidWriterQueueUser != NULL)
				{
					Frame* frameRGBVid = new Frame(*frameRGB);
					frameRGBVid->mat = frameRGB->mat.clone();
					vidWriterQueueUser->push(frameRGBVid);
				}

				if (imgSaverQueueUser != NULL)
				{
					imgSaverQueueUser->push(frameRGB);
				}
				else
				{
					delete frameRGB;
				}
			}

			delete orgFrame;
		}
	}
}

void FrameAnalysator::startNewRound()
{
	// todo
}

