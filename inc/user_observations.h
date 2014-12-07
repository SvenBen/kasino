/*
 * user_observations.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef USER_OBSERVATIONS_H_
#define USER_OBSERVATIONS_H_

#include <boost/shared_ptr.hpp>

enum Hardness
{
	H_DONT_KNOW, H_HARD, H_SOFT
};

enum Rhombe
{
	RHOMBE_N, RHOMBE_NO, RHOMBE_O, RHOMBE_SO, RHOMBE_S, RHOMBE_SW, RHOMBE_W, RHOMBE_NW
};

enum BallDirection
{
	BD_DONT_KNOW, BD_CLOCKWISE, BD_COUNTERCLOCKWISE
};

typedef struct SUserObservations
{
public:
	Rhombe rhombe;
	Hardness hardness;
	BallDirection ballDirection;
} UserObservations;

typedef boost::shared_ptr<UserObservations> SharedUserObservationsPtr;

#endif /* USER_OBSERVATIONS_H_ */
