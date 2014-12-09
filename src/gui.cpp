/*
 * Gui.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#include "gui.h"
#include "kasino_exception.h"

Gui::Gui(Application* app) : app(app),
							 statusWindow(this),
							 logger(&statusWindow, app),
							 statisticWindow(this),
							 frameWindow(this),
							 mainWindow(this, &frameWindow, &statisticWindow)

{
	frameWindow.setMainWindow(&mainWindow);
	statisticWindow.setMainWindow(&mainWindow);
}

Gui::~Gui()
{
}

Gtk::Window* Gui::getMainWindow()
{
	return mainWindow.getGtkWindow();
}

void Gui::log(const std::string& msg, LogLevel logLevel)
{
	logger.log(msg, logLevel);
}
