/*
 * Gui.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#include "gui.h"
#include "macros.h"

Gui::Gui(Application* app) : app(app),
							 statisticWindow(this),
							 frameWindow(this),
							 statusWindow(this),
							 mainWindow(this)
{
	packetReceiver = NULL;
	// TODO
}

Gui::~Gui()
{
	SAFE_DELETE_NULL(packetReceiver)
	// TODO Auto-generated destructor stub
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

void Gui::log(const std::string& msg)
{
	// todo
}
