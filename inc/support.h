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
	static const double SCALE_HD2HIGH;
	static const double SCALE_HD2MEDIUM;
	static const double SCALE_HD2LOW;

private:
	Support();

public:
	static RoundTime velocity2RoundTime(const Velocity& v);
	static Velocity roundTime2Velocity(const RoundTime& rt);
	static double getScaleFactor(StreamQuality quali);
	static cv::Point calcScaledPoint(const cv::Point& inHD, StreamQuality quali);
	static cv::Rect calcScaledRect(const cv::Rect& inHD, StreamQuality quali);
	static cv::Size calcScaledSize(const cv::Size& inHD, StreamQuality quali);
};

#endif /* SUPPORT_H_ */
