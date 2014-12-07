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
#include "packet_receiver.h"

class Gui;

class Window
{
protected:
	const std::string WINDOW_NAME;
	Gui* gui;
	Gtk::Window* window;

public:
	Window(Gui* gui, const std::string& windowName);
	virtual ~Window();

protected:
	virtual void setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder);
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
*/
	ValueDispatcher<SharedFramePtr> newFrameDispatcher;

public:
	FrameWindow(Gui* gui);

private:
	void cbNewFrame();
/*
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
	const std::string SETTINGS_FILE;

	PacketReceiver* packetReceiver;

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

	// dispatchers
	ValueDispatcher<int> newRoundDispatcher;
	ValueDispatcher<int> newCalculatedResultDispatcher;
	Dispatcher packetReceiverDestroyedDispatcher;
	Dispatcher imageSaverDestroyedDispatcher;
	Dispatcher videoWriterDestroyedDispatcher;
	ValueDispatcher<Perspective> perspectiveCalculatedDispatcher;

	SharedUserObservationsPtr userObservations;
	Glib::Threads::Mutex userObsMutex;

public:
	MainWindow(Gui* gui);
	virtual ~MainWindow();
	Gtk::Window* getGtkWindow();
	const SharedUserObservationsPtr getUserObservations();

	void notifyPackerReceiverDestroyed();

private:
	virtual void setUpWindow();
	virtual void setUpCallbacks();
	void loadSettings();
	void saveSettings();
	void resetUserObservations();

	void cbNewRound();
	void cbNewCalculatedResult();
	void cbPacketReceiverDestroyed();
	void cbImageSaverDestroyed();
	void cbVideoWriterDestroyed();
	void cbPerspectiveCalculated();

	void createPacketReceiver();
	void destroyPacketReceiver();
};

class StatisticWindow : Window
{
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;

public:
	StatisticWindow(Gui* gui);

private:
	void setUpCallbacks();
	// todo
};

#endif /* WINDOWS_H_ */
