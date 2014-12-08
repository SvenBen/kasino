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
	frameAnalysator = new FrameAnalysator(&frameWindow);
	if (frameAnalysator == NULL)
	{
		throw NotEnoughSpaceException();
	}
	frameWindow.setMainWindow(&mainWindow);
	statisticWindow.setMainWindow(&mainWindow);
}

Gui::~Gui()
{
	delete frameAnalysator;
}

FrameAnalysator* Gui::getFrameAnalysator() const
{
	return frameAnalysator;
}

Gtk::Window* Gui::getMainWindow()
{
	return mainWindow.getGtkWindow();
}

void Gui::notifyCalculatedResultAvailable()
{
	// todo
}

void Gui::notifyPacketReceiverAvailable()
{
	// todo
}

void Gui::notifyNewRound()
{
	// todo
}

void Gui::notifyNewFrameAvailable()
{
	// todo
}

void Gui::notifyNewStatisticAvailable()
{
	// todo
}

void Gui::log(const std::string& msg, LogLevel logLevel)
{
	logger.log(msg, logLevel);
}
