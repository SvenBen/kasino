/*
 * user_observations.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef USER_OBSERVATIONS_H_
#define USER_OBSERVATIONS_H_

#include <boost/shared_ptr.hpp>

class UserObservations {
public:
	UserObservations();
	virtual ~UserObservations();
};

typedef boost::shared_ptr<UserObservations> SharedUserObservationsPtr;

#endif /* USER_OBSERVATIONS_H_ */
