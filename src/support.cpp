/*
 * support.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include "support.h"

const double Support::SCALE_FACTOR_HD2HIGH = 2/3;
const double Support::SCALE_FACTOR_HD2MEDIUM = 0.5;
const double Support::SCALE_FACTOR_HD2LOW = 0.5;

Support::Support()
{
}

RoundTime Support::velocity2RoundTime(const Velocity& v)
{
	// todo
}

Velocity Support::roundTime2Velocity(const RoundTime& rt)
{
	// todo
}

cv::Point Support::calcPixelPosition(const cv::Point& posInHD, StreamQuality quali)
{
	// todo
}
