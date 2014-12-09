/*
 * image_saver.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef IMAGE_SAVER_H_
#define IMAGE_SAVER_H_

#include "thread.h"
#include "frame.h"
#include "queues.h"

class FrameAnalysator;
class MainWindow;

class ImageSaver : public Thread, public QueueHolder<Frame*>
{
private:
	MainWindow* mainWindow;
	FrameAnalysator* frameAnalysator;
	std::string savePath;
	static unsigned int imgNr;
	static std::string lastSavePath;

public:
	ImageSaver(MainWindow* mainWindow,
			   FrameAnalysator* frameAnalysator,
			   const std::string & savePath);
	virtual ~ImageSaver();

private:
	virtual void threadFunc();
};

#endif /* IMAGE_SAVER_H_ */
