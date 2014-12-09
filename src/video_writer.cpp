/*
 * video_writer.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include "video_writer.h"
#include "windows.h"
#include "queue_holder.h"
#include "kasino_exception.h"

VideoWriter::VideoWriter(MainWindow* mainWindow,
						 FrameAnalysator* frameAnalysator,
						 const std::string & savePath) : QueueHolder(deleteFrameFreeFunc)
{
	this->savePath = savePath;
	this->frameAnalysator = frameAnalysator;
	this->mainWindow = mainWindow;

	thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &VideoWriter::threadFunc));
	frameAnalysator->createFramesForVidWriter(true, this);
	mainWindow->log("VideoWriter created", INFO);
}

VideoWriter::~VideoWriter()
{
	frameAnalysator->createFramesForVidWriter(false);
	quit = true;
	if (thread != NULL)
	{
		thread->join();
	}

	closeVideoFile();
	mainWindow->notifyVideoWriterDestroyed();
	mainWindow->log("VideoWriter destroyed", INFO);
}

void VideoWriter::openVideoFile(int roundNr, const cv::Size2i& size)
{
	assert(!videoWriter.isOpened());
	char number[10];
	sprintf(number, "%04u", roundNr);
	std::string filename = savePath + "/" + number + ".avi";
	videoWriter.open(filename, CV_FOURCC('F', 'L', 'V', '1'), 25, size, true);
	if (!videoWriter.isOpened())
	{
		throw FileOpenException(filename);
	}
}

void VideoWriter::closeVideoFile()
{
	if (videoWriter.isOpened())
	{
		videoWriter.release();
	}
}

void VideoWriter::threadFunc()
{
	while (!quit)
	{
		Frame* frame = timeout_pop();
		if (frame != NULL)
		{
			if (!videoWriter.isOpened())
			{
				openVideoFile(frame->roundNr, cv::Size(frame->mat.cols, frame->mat.rows));
			}
			/* write interleaved video frames */
			videoWriter << frame->mat;
			// todo Macht den Speicher schnell voll!
			delete frame;
		}
	}
}
