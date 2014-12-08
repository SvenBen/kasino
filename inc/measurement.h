/*
 * measurement.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

typedef struct SVelocity
{
	double velocity;
	int64_t measurementTime;
} Velocity;

typedef struct SRoundTime
{
	int64_t roundTime;
	int64_t measurementTime;
} RoundTime;


#endif /* MEASUREMENT_H_ */
