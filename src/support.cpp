/*
 * support.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include "support.h"

const double Support::SCALE_HD2HIGH = 2.0/3.0;
const double Support::SCALE_HD2MEDIUM = 0.5;
const double Support::SCALE_HD2LOW = 0.5;

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

double Support::getScaleFactor(StreamQuality quali)
{
	switch (quali)
	{
	case QUALI_HD:
		return 1;

	case QUALI_HIGH:
		return Support::SCALE_HD2HIGH;

	case QUALI_MEDIUM:
		return Support::SCALE_HD2MEDIUM;

	case QUALI_LOW:
	default:
		return Support::SCALE_HD2LOW;
	}
}

cv::Point Support::calcScaledPoint(const cv::Point& inHD, StreamQuality quali)
{
	/*double scale = getScaleFactor(quali);
	return scale * cv::Point(inHD.x, inHD.y);*/
	return getScaleFactor(quali) * inHD;
}

cv::Rect Support::calcScaledRect(const cv::Rect& inHD, StreamQuality quali)
{
	double scale = getScaleFactor(quali);
	return cv::Rect(cv::Point(scale * inHD.tl().x, scale * inHD.tl().y),
					cv::Point(scale * inHD.br().x, scale * inHD.br().y));
}

cv::Size Support::calcScaledSize(const cv::Size& inHD, StreamQuality quali)
{
	double scale = getScaleFactor(quali);
	return  cv::Size(scale * inHD.width, scale * inHD.height);
}
