/*
 * logger.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

#include "queue_holder.h"
#include "queues.h"

class Logger : QueueHolder<StringQueue, std::string>
{
	// todo
public:
	Logger();
	virtual ~Logger();
};

#endif /* LOGGER_H_ */
