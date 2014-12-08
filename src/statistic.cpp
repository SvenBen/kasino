/*
 * statistic.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#include "statistic.h"
#include "macros.h"

Statistic::Statistic() : DEF_WIDTH(200),
						 DEF_HEIGHT(200)
{
	mat = NULL;
	size.height = DEF_HEIGHT;
	size.width = DEF_WIDTH;

	// TODO Auto-generated constructor stub
}

Statistic::~Statistic()
{
	SAFE_DELETE_NULL(mat)
	// TODO Auto-generated destructor stub
}

void Statistic::drawEmptyStatistic()
{
	// todo
}

void addRoundTime(RoundTime& roundTime)
{
	// todo
}

void Statistic::setSize(const cv::Size2i& size)
{
	this->size = size;
}

cv::Size2i Statistic::getSize() const
{
	return size;
}
