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

class Application;

class Gui {
private:
	Application* app;
	StatusWindow statusWindow;
	Logger logger;
	StatisticWindow statisticWindow;
	FrameWindow frameWindow;
	MainWindow mainWindow;

public:
	Gui(Application* app);
	virtual ~Gui();

	Gtk::Window* getMainWindow();
	void log(const std::string& msg, LogLevel logLevel = INFO);

	void createPacketReceiver();
	void destroyPacketReceiver();
};

#endif /* GUI_H_ */
