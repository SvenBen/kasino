/*
 * Application.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#include "application.h"
#include "kasino_exception.h"

Application::Application(int argc, char* argv[]) : APP_ID("kasino.app"),
							 	 	 	 	 	   quitRequested(false)
{
	app = Gtk::Application::create(argc, argv, APP_ID);
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
	app->run(*gui->getMainWindow());
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
