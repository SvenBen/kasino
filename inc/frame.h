/*
 * frame.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>

#include "enum_types.h"

class Frame
{
public:
	cv::Mat mat;
	Perspective perspective;
	int roundNr;
	int64_t pts;
	int64_t timeSinceRoundStart;
	cv::Point nullPosition;
	cv::Point ballPosition;
	double ballRoundTime;
	double plateRoundTime;
	StreamQuality quali;

public:
	Frame(const cv::Mat& mat);
	Frame(const Frame& frame, const cv::Rect& roi);
};

typedef boost::shared_ptr<Frame> SharedFramePtr;

#endif /* FRAME_H_ */
