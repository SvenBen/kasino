/*
 * windows.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <gtkmm/image.h>
#include <gtkmm/builder.h>
#include <glibmm/threads.h>
#include <string.h>

#include "enum_types.h"
#include "dispatchers.h"
#include "user_observations.h"
#include "queues.h"
#include "queue_user.h"
#include "control_elements.h"

class Gui;

class Window
{
protected:
	const std::string WINDOW_NAME;
	Gui* gui;
	Gtk::Window* window;

public:
	Window(Gui* gui, const std::string& windowName, const std::string& glade_file);
	virtual ~Window();

protected:
	virtual void setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual void setUpCallbacks();
};

class FrameWindow : Window
{
/*
 * todo
 * */
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;
/*
	Gtk::Image* frame_img;
	NewFrameDispatcher newFrameDispatcher;
*/
public:
	FrameWindow(Gui* gui);
/*
private:
	virtual void setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual void setUpCallbacks();
*/
};

class StatusWindow : Window, QueueUser<StringQueue, std::string>
{
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;

public:
	StatusWindow(Gui* gui);

	// todo
};

class MainWindow : Window
{
	friend class StreamControls;

private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;
	const std::string SAVE_SETTINGS_FILE;

	// Represent status of control elements
	StreamQuality selectedStreamQuality;
	std::string selectedServer;
	bool selectedSlowmo;

	// control elements
	StreamControls streamControls;
	ViewOptionsControls viewOptionsControls;
	/*
	 * todo
	 * DataRecordControls dataRecordControls;
	RecordControls recordControls;
	AbcashenControls abcashenControls;*/

	NewRoundDispatcher newRoundDispatcher;
	NewCalculatedResultDispatcher newCalculatedResultDispatcher;
	PacketReceiverDestroyedDispatcher packetReceiverDestroyedDispatcher;
	ImageSaverDestroyedDispatcher imageSaverDestroyedDispatcher;
	VideoWriterDestroyedDispatcher videoWriterDestroyedDispatcher;
	PerspectiveCalculatedDispatcher perspectiveCalculatedDispatcher;
	SharedUserObservationsPtr userObservations;
	Glib::Threads::Mutex userObsMutex;

public:
	MainWindow(Gui* gui);
	virtual ~MainWindow();
	Gtk::Window* getGtkWindow();
	const SharedUserObservationsPtr getUserObservations();

private:
	virtual void setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual void setUpCallbacks();
	void loadDefaultSettings();
	void saveDefaultSettings();
	void resetRoundObservations();
};

class StatisticWindow : Window
{
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;

public:
	StatisticWindow(Gui* gui);

	// todo
};

#endif /* WINDOWS_H_ */
