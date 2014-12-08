/*
 * support.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef SUPPORT_H_
#define SUPPORT_H_

#include <opencv2/core/core.hpp>

#include "measurement.h"
#include "enum_types.h"

class Support
{
private:
	static const double SCALE_FACTOR_HD2HIGH;
	static const double SCALE_FACTOR_HD2MEDIUM;
	static const double SCALE_FACTOR_HD2LOW;

private:
	Support();

public:
	static RoundTime velocity2RoundTime(const Velocity& v);
	static Velocity roundTime2Velocity(const RoundTime& rt);
	static cv::Point calcPixelPosition(const cv::Point& posInHD, StreamQuality quali);
};

#endif /* SUPPORT_H_ */
