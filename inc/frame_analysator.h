/*
 * frame_analysator.h
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#ifndef FRAME_ANALYSATOR_H_
#define FRAME_ANALYSATOR_H_

#include <opencv2/core/core.hpp>
#include <glibmm/threads.h>

extern "C"
{
	#include <libavformat/avformat.h>
}

#include "thread.h"
#include "queue_user.h"
#include "queue_holder.h"

class VideoWriter;
class ImageSaver;
class Frame;
class Round;
class Statistic;
class FrameWindow;
class MainWindow;

class FrameAnalysator : public Thread, public QueueHolder<Frame*>
{
private:
	Round* activeRound;
	Round* lastRound;
	Statistic* activeStatistic;
	FrameWindow* frameWindow;
	MainWindow* mainWindow;
	QueueUser<Frame*>* imgSaverQueueUser;
	QueueUser<Frame*>* vidWriterQueueUser;
	Glib::Threads::Mutex mutex;

public:
	FrameAnalysator(FrameWindow* frameWindow, MainWindow* mainWindow);
	virtual ~FrameAnalysator();

	void createFramesForImgSaver(bool onOff, ImageSaver* imgSaver = NULL);
	void createFramesForVidWriter(bool onOff, VideoWriter* vidWriter = NULL);

private:
	virtual void threadFunc();
	void startNewRound();
};

#endif /* FRAME_ANALYSATOR_H_ */
