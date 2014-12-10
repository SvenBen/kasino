/*
 * perspective_calculator.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: sven
 */

#include "perspective_calculator.h"
#include "frame.h"

PerspectiveCalculator::PerspectiveCalculator()
{
	curPerspective = PERSPECTIVE_UNKNOWN;
}

PerspectiveCalculator::~PerspectiveCalculator()
{
}

Perspective PerspectiveCalculator::calculatePerspective(const Frame& frame)
{
	// todo
	return PERSPECTIVE_UNKNOWN;
}
