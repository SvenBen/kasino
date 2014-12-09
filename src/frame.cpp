/*
 * frame.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#include <limits>

#include "frame.h"

Frame::Frame(const cv::Mat& mat)
{
	this->mat = mat;
	perspective = PERSPECTIVE_UNKNOWN;
	roundNr = -1;
	pts = -1;
	timeSinceRoundStart = -1;
	nullPosition = cv::Point(std::numeric_limits<int>::infinity(), std::numeric_limits<int>::infinity());
	ballPosition = cv::Point(std::numeric_limits<int>::infinity(), std::numeric_limits<int>::infinity());
	ballRoundTime = -1.0;
	plateRoundTime = -1.0;
	quali = QUALI_UNKNOWN;
}

Frame::Frame(const Frame& frame, const cv::Rect& roi)
{
	this->mat = frame.mat(roi);
	perspective = frame.perspective;
	roundNr = frame.roundNr;
	pts = frame.pts;
	timeSinceRoundStart = frame.timeSinceRoundStart;
}

