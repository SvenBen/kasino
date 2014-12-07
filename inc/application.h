/*
 * application.h
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "gui.h"
#include <glibmm/threads.h>
#include <gtkmm/application.h>

class Application
{
private:
	const std::string APP_ID;
	Gui* gui;
	bool quitRequested;
	bool running;
	Glib::Threads::Mutex runningMutex;
	Glib::Threads::Mutex quitMutex;
	Glib::RefPtr<Gtk::Application> app;

public:
	Application(int argc, char* argv[]);
	virtual ~Application();

	void run();
	bool isRunning();
	void setQuitRequested();
	bool getQuitRequested();

private:
	void setRunning(bool running);
};

#endif /* APPLICATION_H_ */
