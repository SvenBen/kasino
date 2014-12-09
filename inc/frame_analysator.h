/*
 * frame_analysator.h
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#ifndef FRAME_ANALYSATOR_H_
#define FRAME_ANALYSATOR_H_

#include <opencv2/core/core.hpp>

extern "C"
{
	#include <libavformat/avformat.h>
}

#include "thread.h"
#include "queue_user.h"
#include "queue_holder.h"

class ImageSaver;
class Frame;
class Round;
class Statistic;
class FrameWindow;

class FrameAnalysator : public Thread, public QueueHolder<Frame*>
{
private:
	Round* activeRound;
	Round* lastRound;
	Statistic* activeStatistic;
	FrameWindow* frameWindow;
	ImageSaver* imgSaver;
	QueueUser<Frame*>* imgSaverQueueUser;

public:
	FrameAnalysator(FrameWindow* frameWindow);
	virtual ~FrameAnalysator();

	void createFramesForImgSaver(bool onOff, ImageSaver* imgSaver = NULL);

private:
	virtual void threadFunc();
	void startNewRound();
};

#endif /* FRAME_ANALYSATOR_H_ */
