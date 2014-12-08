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
#include "queues.h"

class Round;

class FrameAnalysator : public Thread, public QueueHolder<cv::Mat*>
{
private:
	Round* activeRound;
	Round* lastRound;
	cv::Mat* activeStatistic;

public:
	FrameAnalysator();
	virtual ~FrameAnalysator();

private:
	virtual void threadFunc();
	void startNewRound();
};

#endif /* FRAME_ANALYSATOR_H_ */
