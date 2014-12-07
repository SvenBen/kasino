/*
 * logger.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

#include "queues.h"

class StatusWindow;
class Application;

class Logger : public QueueUser<std::string*>
{
private:
	StatusWindow* statusWindow;
	Application* app;
	// todo
public:
	Logger(StatusWindow* statusWindow, Application* app);
	virtual ~Logger();

	void log(const std::string& msg);
};


#endif /* LOGGER_H_ */
