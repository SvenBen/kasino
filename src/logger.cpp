/*
 * logger.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#include "logger.h"
#include "windows.h"
#include "kasino_strings.h"
#include "kasino_exception.h"
#include "application.h"

Logger::Logger(StatusWindow* statusWindow, Application* app) :
	QueueUser(statusWindow)
{
	this->app = app;
	this->statusWindow = statusWindow;
}

Logger::~Logger()
{
}

void Logger::log(const std::string& msg)
{
	if (app->isRunning())
	{
		std::string* copy = new std::string(msg);
		if (copy == NULL)
			throw KasinoException(STR_NOT_ENOUGH_SPACE);

		push(copy);
		statusWindow->notifyNewStatus();
	}
	else
	{
		std::cerr << msg << std::endl;
	}
}
