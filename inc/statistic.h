/*
 * statistic.h
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#ifndef STATISTIC_H_
#define STATISTIC_H_

#include <opencv2/core/core.hpp>

#include "measurement.h"

class Statistic
{
private:
	const int DEF_WIDTH;
	const int DEF_HEIGHT;
	cv::Size2i size;
	cv::Mat* mat;

public:
	Statistic();
	virtual ~Statistic();
	void drawEmptyStatistic();
	void addRoundTime(RoundTime& roundTime);
	void setSize(const cv::Size2i& size);
	cv::Size2i getSize() const;
};

#endif /* STATISTIC_H_ */
