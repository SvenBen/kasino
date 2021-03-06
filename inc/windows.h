/*
 * windows.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <gtkmm/image.h>
#include <gtkmm/textview.h>
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
#include "image_saver.h"
#include "video_writer.h"
#include "frame.h"
#include "logger.h"

class Gui;
class StatisticWindow;

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
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;

	Gtk::Image* frame_img;
	ValueDispatcher<SharedFramePtr> newFrameDispatcher;
	MainWindow* mainWindow;
	Glib::Threads::Mutex visibleMutex;
	bool visible;

public:
	FrameWindow(Gui* gui);
	void notifyNewFrame(SharedFramePtr sharedFrame);
	void setVisible(bool v);
	bool getVisible();
	void setMainWindow(MainWindow* mainWindow);

private:
	void setUpWindow();
	void setUpCallbacks();
	void cbNewFrame();
	void cbWindowHidden();
};

class StatusWindow : Window, public QueueHolder<std::string*>
{
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;
	Gtk::TextView* status;
	Dispatcher newStatusDispatcher;

public:
	StatusWindow(Gui* gui);
	void notifyNewStatus();

protected:
	void setUpWindow();
	void addToLog(const std::string& msg);
	void cbNewStatus();
};

class MainWindow : Window
{
	friend class StreamControls;
	friend class RecordControls;
	friend class DataRecordControls;
	friend class ViewOptionsControls;

private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;
	const std::string SETTINGS_FILE;

	PacketReceiver* packetReceiver;
	ImageSaver* imageSaver;
	VideoWriter* videoWriter;
	FrameWindow* frameWindow;
	StatisticWindow* statisticWindow;
	FrameAnalysator* frameAnalysator;

	// Represent status of control elements
	StreamQuality selectedStreamQuality;
	std::string selectedServer;
	int selectedServerIndex;
	bool selectedSlowmo;
	bool viewFrameWindowChecked;
	bool viewStatisticWindowChecked;
	bool viewCalculatedPerspectiveChecked;
	bool viewRoundNrChecked;
	bool viewBallPositionChecked;
	bool viewNullPositionChecked;
	bool viewCrosshairChecked;
	bool viewTimeSinceRoundStartChecked;
	bool viewBallVelocityChecked;
	bool viewPlateVelocityChecked;
	bool viewPerspectiveCalculationChecked;
	bool viewNullPosCalculationChecked;
	bool viewBallPosCalculationChecked;
	std::string videoRecordPath;
	std::string imageRecordPath;
	UserObservations userObservations;
	bool analyze;
	bool recordRound;
	std::string pathRoundLogFile;

	// control elements
	StreamControls streamControls;
	ViewOptionsControls viewOptionsControls;
	RecordControls recordControls;
	DataRecordControls dataRecordControls;
	/* todo AbcashenControls abcashenControls;*/

	// dispatchers
	ValueDispatcher<int> newRoundDispatcher;
	ValueDispatcher<int> newCalculatedResultDispatcher;
	Dispatcher packetReceiverDestroyedDispatcher;
	Dispatcher statisticWindowHiddenDispatcher;
	Dispatcher frameWindowHiddenDispatcher;
	Dispatcher imageSaverDestroyedDispatcher;
	Dispatcher videoWriterDestroyedDispatcher;
	ValueDispatcher<Perspective> perspectiveCalculatedDispatcher;

	Glib::Threads::Mutex controlValueMutex;

public:
	MainWindow(Gui* gui, FrameWindow* fw, StatisticWindow* sw);
	virtual ~MainWindow();

	Gtk::Window* getGtkWindow();
	const UserObservations getUserObservations();
	bool viewCalculatedPerspective();
	bool viewRoundNr();
	bool viewBallPosition();
	bool viewNullPosition();
	bool viewCrosshair();
	bool viewTimeSinceRoundStart();
	bool viewBallVelocity();
	bool viewPlateVelocity();
	bool viewPerspectiveCalculation();
	bool viewNullPosCalculation();
	bool viewBallPosCalculation();

	void notifyPerspectiveCalculated(Perspective p);
	void notifyPacketReceiverDestroyed();
	void notifyImageSaverDestroyed();
	void notifyVideoWriterDestroyed();
	void notifyFrameWindowHidden();
	void notifyStatisticWindowHidden();
	void notifyNewRoundStarted(int round);

	void log(const std::string& msg, LogLevel logLevel = INFO);

private:
	virtual void setUpWindow();
	virtual void setUpCallbacks();
	void loadSettings();
	void saveSettings();
	void resetUserObservations();

	void cbNewRound();
	void cbNewCalculatedResult();
	void cbPacketReceiverDestroyed();
	void cbFrameWindowHidden();
	void cbStatisticWindowHidden();
	void cbImageSaverDestroyed();
	void cbVideoWriterDestroyed();
	void cbPerspectiveCalculated();

	void createPacketReceiver();
	void destroyPacketReceiver();
	void createImageSaver();
	void destroyImageSaver();
	void createVideoWriter();
	void destroyVideoWriter();
};

class StatisticWindow : Window
{
private:
	static const std::string GLADE_FILE;
	static const std::string WINDOW_NAME;

	MainWindow* mainWindow;
	Gtk::Image* statistic_img;

public:
	StatisticWindow(Gui* gui);
	void setVisible(bool v);
	void setMainWindow(MainWindow* mainWindow);

private:
	void setUpWindow();
	void setUpCallbacks();
	void cbWindowHidden();
	// todo
};

#endif /* WINDOWS_H_ */
