/*
 * Application.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#include "application.h"
#include "kasino_exception.h"

Application::Application(int argc, char* argv[]) : APP_ID("kasino.app")
{
	quitRequested = false;
	running = false;
	app = Gtk::Application::create(argc, argv, APP_ID);
	// notwendig? Glib::thread_init();
	gui = new Gui(this);
	if (gui == NULL)
	{
		throw KasinoException("Speicher ist voll");
	}
}

Application::~Application()
{
	delete gui;
	gui = NULL;
}

void Application::run()
{
	setRunning(true);
	app->run(*gui->getMainWindow());
	setRunning(false);
}

void Application::setRunning(bool running)
{
	Glib::Threads::Mutex::Lock lock(runningMutex);
	this->running = running;
}

bool Application::isRunning()
{
	Glib::Threads::Mutex::Lock lock(runningMutex);
	return running;
}

void Application::setQuitRequested()
{
	Glib::Threads::Mutex::Lock lock(quitMutex);
	if (!quitRequested)
	{
		quitRequested = true;
		app->quit();
	}
}

bool Application::getQuitRequested()
{
	Glib::Threads::Mutex::Lock lock(quitMutex);
	return quitRequested;
}
