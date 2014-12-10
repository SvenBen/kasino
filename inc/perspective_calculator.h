/*
 * perspective_calculator.h
 *
 *  Created on: Dec 9, 2014
 *      Author: sven
 */

#ifndef PERSPECTIVE_CALCULATOR_H_
#define PERSPECTIVE_CALCULATOR_H_

#include "enum_types.h"

class Frame;

class PerspectiveCalculator
{
private:
	Perspective curPerspective;

public:
	PerspectiveCalculator();
	virtual ~PerspectiveCalculator();

	Perspective calculatePerspective(const Frame& frame);
};

#endif /* PERSPECTIVE_CALCULATOR_H_ */
