/*
 * frame.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#include "frame.h"

Frame::Frame(const cv::Mat& mat)
{
	this->mat = mat;
	perspective = PERSPECTIVE_UNKNOWN;
	roundNr = -1;
	pts = -1;
	timeSinceRoundStart = -1;
	// TODO Auto-generated constructor stub
}

Frame::Frame(const Frame& frame, const cv::Rect& roi)
{
	this->mat = frame.mat(roi);
	perspective = frame.perspective;
	roundNr = frame.roundNr;
	pts = frame.pts;
	timeSinceRoundStart = frame.timeSinceRoundStart;
}

Frame::~Frame()
{
	// TODO Auto-generated destructor stub
}

