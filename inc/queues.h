/*
 * queues.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef QUEUES_H_
#define QUEUES_H_

#include <glib.h>
#include <opencv2/core/core.hpp>
#include <string>

extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavutil/avutil.h>
}

#include "round.h"
#include "frame.h"

template <class ElementType>
class AsyncQueue
{
	// todo
};

class PacketQueue : AsyncQueue<AVPacket*>
{
	// todo
};

class MatQueue : AsyncQueue<cv::Mat*>
{
	// todo
};

class RoundQueue : AsyncQueue<Round*>
{
	// todo
};

class SharedFrameQueue : AsyncQueue<SharedFramePtr>
{
	// todo
};

class StringQueue : AsyncQueue<std::string>
{
public:
	StringQueue();
	// todo
};

#endif /* QUEUES_H_ */
