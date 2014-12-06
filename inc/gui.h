/*
 * gui.h
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#ifndef GUI_H_
#define GUI_H_

#include <gtkmm/window.h>

#include "windows.h"
#include "logger.h"
#include "packet_receiver.h"

class Application;

class Gui {
private:
	Application* app;
	PacketReceiver* packetReceiver;
	StatisticWindow statisticWindow;
	FrameWindow frameWindow;
	StatusWindow statusWindow;
	MainWindow mainWindow;
	Logger logger;

public:
	Gui(Application* app);
	virtual ~Gui();

	Gtk::Window* getMainWindow();
	void notifyCalculatedResultAvailable();
	void notifyPacketReceiverAvailable();
	void notifyNewRound();
	void notifyNewFrameAvailable();
	void notifyNewStatisticAvailable();
	void log(const std::string& msg);
};

#endif /* GUI_H_ */
