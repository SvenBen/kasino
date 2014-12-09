/*
 * image_saver.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include <opencv2/highgui/highgui.hpp>
#include <string>

#include "image_saver.h"
#include "frame_analysator.h"
#include "windows.h"

unsigned int ImageSaver::imgNr = 0;
std::string ImageSaver::lastSavePath = "";

ImageSaver::ImageSaver(MainWindow* mainWindow,
					   FrameAnalysator* frameAnalysator,
					   const std::string & savePath)
{
	this->mainWindow = mainWindow;
	this->frameAnalysator = frameAnalysator;

	// Bei neuem Speicherort die ImgNr zurücksetzen, für die Dateibenennung
	if (ImageSaver::lastSavePath != savePath)
	{
		ImageSaver::imgNr = 0;
	}

	ImageSaver::lastSavePath = savePath;
	this->savePath = savePath;
	thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &ImageSaver::threadFunc));
	frameAnalysator->createFramesForImgSaver(true, this);
	mainWindow->log("ImageSaver created", INFO);
}

ImageSaver::~ImageSaver()
{
	frameAnalysator->createFramesForImgSaver(false);
	quit = true;
	if (thread != NULL)
	{
		thread->join();
	}

	mainWindow->notifyImageSaverDestroyed();
	mainWindow->log("ImageSaver destroyed", INFO);
}

void ImageSaver::threadFunc()
{
	while (!quit)
	{
		Frame* frame = timeout_pop();
		if (frame != NULL)
		{
			char number[11];
			sprintf(number, "%05u.jpg", ImageSaver::imgNr++);
			std::string filename(number + std::string(".png"));
			cv::imwrite(savePath + "/" + filename, frame->mat);
			delete frame;
		}
	}
}
