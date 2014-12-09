
#include <opencv2/imgproc/imgproc.hpp>
#include <gtkmm/window.h>
#include <assert.h>
#include <iostream>
#include <string>

#include "windows.h"
#include "macros.h"
#include "kasino_exception.h"
#include "kasino_strings.h"
#include "gui.h"

Window::Window(Gui* gui, const std::string& windowName) :
			WINDOW_NAME(windowName)
{
	window = NULL;
	this->gui = gui;
}

Window::~Window()
{
	// todo
}

void Window::setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder)
{
	builder->get_widget(WINDOW_NAME, window);
	// wird in der abgeleiteten Klasse implementiert
}


const std::string FrameWindow::GLADE_FILE = "gui/frame_window.glade";
const std::string FrameWindow::WINDOW_NAME = "frame_window";

FrameWindow::FrameWindow(Gui* gui) :
		Window(gui, FrameWindow::WINDOW_NAME),
		newFrameDispatcher(sigc::mem_fun(*this, &FrameWindow::cbNewFrame))
{
	mainWindow = NULL;
	frame_img = NULL;
	visible = false;
	setUpWindow();
	setUpCallbacks();
}

void FrameWindow::notifyNewFrame(SharedFramePtr sharedFrame)
{
	newFrameDispatcher.notify(sharedFrame);
}

void FrameWindow::setVisible(bool v)
{
	Glib::Threads::Mutex::Lock lock(visibleMutex);
	visible = v;
	if (v)
	{
		window->show_all();
	}
	else
	{
		window->hide();
	}
}

bool FrameWindow::getVisible()
{
	Glib::Threads::Mutex::Lock lock(visibleMutex);
	return visible;
}

void FrameWindow::setMainWindow(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
}

void FrameWindow::setUpWindow()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_FILE);
	Window::setUpWindow(builder);
	builder->get_widget("frame_img", frame_img);
}
void FrameWindow::setUpCallbacks()
{
	window->signal_hide().connect(sigc::mem_fun(*this, &FrameWindow::cbWindowHidden));
}

void FrameWindow::cbNewFrame()
{
	SharedFramePtr sharedFrame = newFrameDispatcher.getValue();
	frame_img->set(Gdk::Pixbuf::create_from_data(sharedFrame->mat.data, Gdk::COLORSPACE_RGB, false, 8, sharedFrame->mat.cols, sharedFrame->mat.rows, sharedFrame->mat.step));
	frame_img->queue_draw();
}

void FrameWindow::cbWindowHidden()
{
	if (mainWindow != NULL)
	{
		mainWindow->notifyFrameWindowHidden();
	}
}

const std::string StatusWindow::GLADE_FILE = "gui/status_window.glade";
const std::string StatusWindow::WINDOW_NAME = "status_window";

StatusWindow::StatusWindow(Gui* gui) :
		Window(gui, StatusWindow::WINDOW_NAME),
		QueueHolder(deleteStringFreeFunc),
		newStatusDispatcher(sigc::mem_fun(*this, &StatusWindow::cbNewStatus))
{
	setUpWindow();
	window->show_all();
}

void StatusWindow::notifyNewStatus()
{
	newStatusDispatcher.notify();
}

void StatusWindow::setUpWindow()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_FILE);
	Window::setUpWindow(builder);
	builder->get_widget("status", status);
}

void StatusWindow::addToLog(const std::string& msg)
{
	Glib::RefPtr<Gtk::TextBuffer> buf = status->get_buffer();
	buf->insert_at_cursor(msg + "\n");
}

void StatusWindow::cbNewStatus()
{

	while (true)
	{
		std::string* msg = try_pop();
		if (msg == NULL)
		{
			break;
		}

		addToLog(*msg);
		delete msg;
	}
}


const std::string MainWindow::GLADE_FILE = "gui/main_window.glade";
const std::string MainWindow::WINDOW_NAME = "main_window";

MainWindow::MainWindow(Gui* gui, FrameWindow* fw, StatisticWindow* sw) :
		Window(gui, MainWindow::WINDOW_NAME),
	    SETTINGS_FILE("gui/gui_settings.xml"),
	    streamControls(this),
	    viewOptionsControls(this),
	    recordControls(this),
	    dataRecordControls(this),
	    newRoundDispatcher(sigc::mem_fun(*this, &MainWindow::cbNewRound)),
	    newCalculatedResultDispatcher(sigc::mem_fun(*this, &MainWindow::cbNewCalculatedResult)),
	    packetReceiverDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbPacketReceiverDestroyed)),
	    statisticWindowHiddenDispatcher(sigc::mem_fun(*this, &MainWindow::cbStatisticWindowHidden)),
	    frameWindowHiddenDispatcher(sigc::mem_fun(*this, &MainWindow::cbFrameWindowHidden)),
	    imageSaverDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbImageSaverDestroyed)),
	    videoWriterDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbVideoWriterDestroyed)),
	    perspectiveCalculatedDispatcher(sigc::mem_fun(*this, &MainWindow::cbPerspectiveCalculated))
{
	packetReceiver = NULL;
	imageSaver = NULL;
	videoWriter = NULL;
	statisticWindow = sw;
	frameWindow = fw;
	setUpWindow();
	setUpCallbacks();

	frameAnalysator = new FrameAnalysator(frameWindow, this);
	if (frameAnalysator == NULL)
	{
		throw NotEnoughSpaceException();
	}

	selectedStreamQuality = QUALI_HD;
	selectedServerIndex = streamControls.servers->get_active_row_number();
	selectedServer = streamControls.servers->get_active_text();
	selectedSlowmo = true;
	viewFrameWindowChecked = false;
	viewStatisticWindowChecked = false;
	viewCalculatedPerspectiveChecked = false;
	viewRoundNrChecked = false;
	viewBallPositionChecked = false;
	viewNullPositionChecked = false;
	viewCrosshairChecked = false;
	viewTimeSinceRoundStartChecked = false;
	viewBallVelocityChecked = false;
	viewPlateVelocityChecked = false;
	viewPerspectiveCalculationChecked = false;
	viewNullPosCalculationChecked = false;
	viewBallPosCalculationChecked = false;
	videoRecordPath = "";
	imageRecordPath = "";
	userObservations.ballDirection = BD_DONT_KNOW;
	userObservations.hardness = H_DONT_KNOW;
	userObservations.rhombe = RHOMBE_DONT_KNOW;
	userObservations.resultNumber = -1;
	analyze = false;
	recordRound = false;
	pathRoundLogFile = "";

	frameWindow->setVisible(viewFrameWindowChecked);
	statisticWindow->setVisible(viewStatisticWindowChecked);

	try
	{
		loadSettings();
	}
	catch (KasinoException& e)
	{
		gui->log(e.what(), WARNING);
	}
	catch (cv::Exception& e)
	{
		gui->log(e.what(), WARNING);
	}
}

MainWindow::~MainWindow()
{
	SAFE_DELETE_NULL(imageSaver)
	SAFE_DELETE_NULL(videoWriter)
	SAFE_DELETE_NULL(packetReceiver)
	SAFE_DELETE_NULL(frameAnalysator)
	try
	{
		saveSettings();
	}
	catch (KasinoException& e)
	{
		// todo log message
	}
}

Gtk::Window* MainWindow::getGtkWindow()
{
	return window;
}

const UserObservations MainWindow::getUserObservations()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return userObservations;
}

bool MainWindow::viewCalculatedPerspective()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewCalculatedPerspectiveChecked;
}

bool MainWindow::viewRoundNr()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewRoundNrChecked;
}

bool MainWindow::viewBallPosition()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewBallPositionChecked;
}

bool MainWindow::viewNullPosition()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewNullPositionChecked;
}

bool MainWindow::viewCrosshair()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewCrosshairChecked;
}

bool MainWindow::viewTimeSinceRoundStart()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewTimeSinceRoundStartChecked;
}

bool MainWindow::viewBallVelocity()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewBallVelocityChecked;
}

bool MainWindow::viewPlateVelocity()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewPlateVelocityChecked;
}

bool MainWindow::viewPerspectiveCalculation()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewPerspectiveCalculationChecked;
}

bool MainWindow::viewNullPosCalculation()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewNullPosCalculationChecked;
}

bool MainWindow::viewBallPosCalculation()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	return viewBallPosCalculationChecked;
}

void MainWindow::setUpWindow()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_FILE);
	Window::setUpWindow(builder);

	streamControls.setUpControlElements(builder);
	viewOptionsControls.setUpControlElements(builder);
	recordControls.setUpControlElements(builder);
	dataRecordControls.setUpControlElements(builder);
	// todo
}

void MainWindow::setUpCallbacks()
{
	streamControls.setUpCallbacks();
	viewOptionsControls.setUpCallbacks();
	recordControls.setUpCallbacks();
	dataRecordControls.setUpCallbacks();
	// todo
}

void MainWindow::loadSettings()
{
	cv::FileStorage settings(SETTINGS_FILE, cv::FileStorage::READ);
	if (settings.isOpened())
	{
		// Stream Settings
		if (settings[STR_SETTING_SLOWMO].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_SLOWMO] >> selectedSlowmo;
			if (selectedSlowmo)
			{
				streamControls.slowmotion_on->set_active();
			}
			else
			{
				streamControls.slowmotion_off->set_active();
			}
		}
		else
		{
			log("Setting \"" + STR_SETTING_SLOWMO + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		if (settings[STR_SETTING_QUALI].type() == cv::FileNode::INT)
		{
			int quali;
			settings[STR_SETTING_QUALI] >> quali;
			switch (quali)
			{
			case QUALI_HD:
				streamControls.quali_hd->set_active();
				selectedStreamQuality = QUALI_HD;
				break;

			case QUALI_HIGH:
				streamControls.quali_high->set_active();
				selectedStreamQuality = QUALI_HIGH;
				break;

			case QUALI_MEDIUM:
				streamControls.quali_medium->set_active();
				selectedStreamQuality = QUALI_MEDIUM;
				break;

			case QUALI_LOW:
				streamControls.quali_low->set_active();
				selectedStreamQuality = QUALI_LOW;
				break;
			default:
				throw KasinoException(STR_ERR_READING_SETTINGS);
			}
		}
		else
		{
			log("Setting \"" + STR_SETTING_QUALI + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		if (settings[STR_SETTING_SERVER].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_SERVER] >> selectedServerIndex;
			streamControls.servers->set_active(selectedServerIndex);
			selectedServer = streamControls.servers->get_active_text();
		}
		else
		{
			log("Setting \"" + STR_SETTING_SERVER + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		// ViewOptions Settings
		if (settings[STR_SETTING_VIEW_FRAME_WINDOW].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_FRAME_WINDOW] >> viewFrameWindowChecked;
			viewOptionsControls.view_frame_window->set_active(viewFrameWindowChecked);
			frameWindow->setVisible(viewFrameWindowChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_FRAME_WINDOW + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_STATISTIC_WINDOW].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_STATISTIC_WINDOW] >> viewStatisticWindowChecked;
			viewOptionsControls.view_statistic_window->set_active(viewStatisticWindowChecked);
			statisticWindow->setVisible(viewStatisticWindowChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_STATISTIC_WINDOW + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_CALCULATED_PERSPECTIVE].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_CALCULATED_PERSPECTIVE] >> viewCalculatedPerspectiveChecked;
			viewOptionsControls.view_calculated_perspective->set_active(viewCalculatedPerspectiveChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_CALCULATED_PERSPECTIVE + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_ROUND_NR].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_ROUND_NR] >> viewRoundNrChecked;
			viewOptionsControls.view_round_nr->set_active(viewRoundNrChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_ROUND_NR + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_BALL_POSITION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_POSITION] >> viewBallPositionChecked;
			viewOptionsControls.view_ball_position->set_active(viewBallPositionChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_BALL_POSITION + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_NULL_POSITION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_NULL_POSITION] >> viewNullPositionChecked;
			viewOptionsControls.view_null_position->set_active(viewNullPositionChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_NULL_POSITION + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_CROSSHAIR].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_CROSSHAIR] >> viewCrosshairChecked;
			viewOptionsControls.view_crosshair->set_active(viewCrosshairChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_CROSSHAIR + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_TIME_SINCE_ROUND_START].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_TIME_SINCE_ROUND_START] >> viewTimeSinceRoundStartChecked;
			viewOptionsControls.view_time_since_round_start->set_active(viewTimeSinceRoundStartChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_TIME_SINCE_ROUND_START + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_BALL_VELOCITY].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_VELOCITY] >> viewBallVelocityChecked;
			viewOptionsControls.view_ball_velocity->set_active(viewBallVelocityChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_BALL_VELOCITY + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_PLATE_VELOCITY].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_PLATE_VELOCITY] >> viewPlateVelocityChecked;
			viewOptionsControls.view_plate_velocity->set_active(viewPlateVelocityChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_PLATE_VELOCITY + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_PERSPECTIVE_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_PERSPECTIVE_CALCULATION] >> viewPerspectiveCalculationChecked;
			viewOptionsControls.view_perspective_calculation->set_active(viewPerspectiveCalculationChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_PERSPECTIVE_CALCULATION + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_NULL_POS_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_NULL_POS_CALCULATION] >> viewNullPosCalculationChecked;
			viewOptionsControls.view_null_pos_calculation->set_active(viewNullPosCalculationChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_NULL_POS_CALCULATION + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_VIEW_BALL_POS_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_POS_CALCULATION] >> viewBallPosCalculationChecked;
			viewOptionsControls.view_ball_pos_calculation->set_active(viewBallPosCalculationChecked);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIEW_BALL_POS_CALCULATION + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		// Record Settings
		if (settings[STR_SETTING_VIDEO_RECORD_PATH].type() == cv::FileNode::STRING)
		{
			settings[STR_SETTING_VIDEO_RECORD_PATH] >> videoRecordPath;
			recordControls.video_record_path->set_filename(videoRecordPath);
		}
		else
		{
			log("Setting \"" + STR_SETTING_VIDEO_RECORD_PATH + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}
		if (settings[STR_SETTING_IMAGE_RECORD_PATH].type() == cv::FileNode::STRING)
		{
			settings[STR_SETTING_IMAGE_RECORD_PATH] >> imageRecordPath;
			recordControls.image_record_path->set_filename(imageRecordPath);
		}
		else
		{
			log("Setting \"" + STR_SETTING_IMAGE_RECORD_PATH + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		if (settings[STR_SETTING_ANALYZE].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_ANALYZE] >> analyze;
			dataRecordControls.analyze->set_active(analyze);
		}
		else
		{
			log("Setting \"" + STR_SETTING_ANALYZE + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

		if (settings[STR_SETTING_PATH_ROUND_LOG_FILE].type() == cv::FileNode::STRING)
		{
			settings[STR_SETTING_PATH_ROUND_LOG_FILE] >> pathRoundLogFile;
			dataRecordControls.path_round_log_file->set_filename(pathRoundLogFile);
		}
		else
		{
			log("Setting \"" + STR_SETTING_PATH_ROUND_LOG_FILE + "\" beim Parsen von " + SETTINGS_FILE + " nicht geladen", WARNING);
		}

	}
	else
	{
		throw KasinoException(STR_CANNOT_OPEN_FILE(SETTINGS_FILE));
	}

	settings.release();
}

void MainWindow::saveSettings()
{
	Glib::Threads::Mutex::Lock lock(controlValueMutex);
	cv::FileStorage settings(SETTINGS_FILE, cv::FileStorage::WRITE);
	if (settings.isOpened())
	{
		// Stream Settings
		settings << STR_SETTING_SLOWMO << selectedSlowmo;
		settings << STR_SETTING_QUALI << selectedStreamQuality;
		settings << STR_SETTING_SERVER << streamControls.servers->get_active_row_number();

		// ViewOptions Settings
		settings << STR_SETTING_VIEW_FRAME_WINDOW << viewFrameWindowChecked;
		settings << STR_SETTING_VIEW_STATISTIC_WINDOW << viewStatisticWindowChecked;
		settings << STR_SETTING_VIEW_CALCULATED_PERSPECTIVE << viewCalculatedPerspectiveChecked;
		settings << STR_SETTING_VIEW_ROUND_NR << viewRoundNrChecked;
		settings << STR_SETTING_VIEW_BALL_POSITION << viewBallPositionChecked;
		settings << STR_SETTING_VIEW_NULL_POSITION << viewNullPositionChecked;
		settings << STR_SETTING_VIEW_CROSSHAIR << viewCrosshairChecked;
		settings << STR_SETTING_VIEW_TIME_SINCE_ROUND_START << viewTimeSinceRoundStartChecked;
		settings << STR_SETTING_VIEW_BALL_VELOCITY << viewBallVelocityChecked;
		settings << STR_SETTING_VIEW_PLATE_VELOCITY << viewPlateVelocityChecked;
		settings << STR_SETTING_VIEW_PERSPECTIVE_CALCULATION << viewPerspectiveCalculationChecked;
		settings << STR_SETTING_VIEW_NULL_POS_CALCULATION << viewNullPosCalculationChecked;
		settings << STR_SETTING_VIEW_BALL_POS_CALCULATION << viewBallPosCalculationChecked;

		// Record Settings
		settings << STR_SETTING_VIDEO_RECORD_PATH << videoRecordPath;
		settings << STR_SETTING_IMAGE_RECORD_PATH << imageRecordPath;

		// DataRecord Settings
		settings << STR_SETTING_ANALYZE << analyze;
		settings << STR_SETTING_PATH_ROUND_LOG_FILE <<  pathRoundLogFile;
	}
	else
	{
		throw KasinoException(STR_CANNOT_OPEN_FILE(SETTINGS_FILE));
	}

	settings.release();

	/*
	 * analyze
	path_round_log_file

	*/
}

void MainWindow::resetUserObservations()
{
	dataRecordControls.ball_direction_dont_know->set_active();
	dataRecordControls.rhombe_dont_know->set_active();
	dataRecordControls.rhombe_hit_dont_know->set_active();
	dataRecordControls.result_number->set_value(-1);
}

void MainWindow::cbNewRound()
{
	resetUserObservations();
	dataRecordControls.round_nr->set_text(std::to_string(newRoundDispatcher.getValue()));
	dataRecordControls.perspective_nr->set_text("");
}

void MainWindow::cbNewCalculatedResult()
{
	// todo
}

void MainWindow::cbPacketReceiverDestroyed()
{
	streamControls.btn_start_stream->set_sensitive(true);
	streamControls.btn_stop_stream->set_sensitive(false);
}

void MainWindow::cbFrameWindowHidden()
{
	controlValueMutex.lock();
	viewFrameWindowChecked = false;
	bool view = viewFrameWindowChecked;
	controlValueMutex.unlock();
	// Muss wieder entlockt werden, sonst Deadlock
	viewOptionsControls.view_frame_window->set_active(view);
}

void MainWindow::cbStatisticWindowHidden()
{
	controlValueMutex.lock();
	viewStatisticWindowChecked = false;
	bool view = viewStatisticWindowChecked;
	controlValueMutex.unlock();
	// Muss wieder entlockt werden, sonst Deadlock
	viewOptionsControls.view_statistic_window->set_active(view);
}

void MainWindow::cbImageSaverDestroyed()
{
	recordControls.image_record_start->set_sensitive(true);
	recordControls.image_record_stop->set_sensitive(false);
}

void MainWindow::cbVideoWriterDestroyed()
{
	recordControls.video_record_start->set_sensitive(true);
	recordControls.video_record_stop->set_sensitive(false);
}

void MainWindow::cbPerspectiveCalculated()
{
	// todo
}

void MainWindow::createPacketReceiver()
{
	try
	{
		controlValueMutex.lock();
		Stream stream(selectedStreamQuality, selectedSlowmo, selectedServer);
		controlValueMutex.unlock();
		packetReceiver = new PacketReceiver(stream, this, frameAnalysator);
		if (packetReceiver == NULL)
		{
			throw NotEnoughSpaceException();
		}
	}
	catch (Glib::Exception& e)
	{
		log(e.what(), ERROR);
	}
	catch (KasinoException& e)
	{
		log(e.what(), ERROR);
	}
}

void MainWindow::destroyPacketReceiver()
{
	SAFE_DELETE_NULL(packetReceiver)
}

void MainWindow::createImageSaver()
{
	try
	{
		imageSaver = new ImageSaver(this, frameAnalysator, imageRecordPath);
		if (imageSaver == NULL)
		{
			throw NotEnoughSpaceException();
		}
	}
	catch (Glib::Exception& e)
	{
		log(e.what(), ERROR);
	}
	catch (KasinoException& e)
	{
		log(e.what(), ERROR);
	}
	catch (cv::Exception& e)
	{
		log(e.what(), ERROR);
	}
}

void MainWindow::destroyImageSaver()
{
	SAFE_DELETE_NULL(imageSaver)
}

void MainWindow::createVideoWriter()
{
	try
	{
		videoWriter = new VideoWriter(this, frameAnalysator, videoRecordPath);
		if (videoWriter == NULL)
		{
			throw NotEnoughSpaceException();
		}
	}
	catch (Glib::Exception& e)
	{
		log(e.what(), ERROR);
	}
	catch (KasinoException& e)
	{
		log(e.what(), ERROR);
	}
	catch (cv::Exception& e)
	{
		log(e.what(), ERROR);
	}
}

void MainWindow::destroyVideoWriter()
{
	SAFE_DELETE_NULL(videoWriter)
}

void MainWindow::notifyPacketReceiverDestroyed()
{
	packetReceiverDestroyedDispatcher.notify();
}

void MainWindow::notifyImageSaverDestroyed()
{
	imageSaverDestroyedDispatcher.notify();
}

void MainWindow::notifyVideoWriterDestroyed()
{
	videoWriterDestroyedDispatcher.notify();
}

void MainWindow::notifyFrameWindowHidden()
{
	frameWindowHiddenDispatcher.notify();
}

void MainWindow::notifyStatisticWindowHidden()
{
	statisticWindowHiddenDispatcher.notify();
}

void MainWindow::notifyNewRoundStarted(int round)
{
	newRoundDispatcher.notify(round);
}

void MainWindow::log(const std::string& msg, LogLevel logLevel)
{
	gui->log(msg, logLevel);
}


const std::string StatisticWindow::GLADE_FILE = "gui/statistic_window.glade";
const std::string StatisticWindow::WINDOW_NAME = "statistic_window";

StatisticWindow::StatisticWindow(Gui* gui) :
		Window(gui, StatisticWindow::WINDOW_NAME)
{
	mainWindow = NULL;
	statistic_img = NULL;
	setUpWindow();
	setUpCallbacks();
	// todo
}

void StatisticWindow::setVisible(bool v)
{
	if (v)
	{
		window->show_all();
	}
	else
	{
		window->hide();
	}
}

void StatisticWindow::setMainWindow(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
}

void StatisticWindow::setUpWindow()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_FILE);
	Window::setUpWindow(builder);
	builder->get_widget("statistic_img", statistic_img);
}

void StatisticWindow::setUpCallbacks()
{
	window->signal_hide().connect(sigc::mem_fun(*this, &StatisticWindow::cbWindowHidden));
}

void StatisticWindow::cbWindowHidden()
{
	if (mainWindow != NULL)
	{
		mainWindow->notifyStatisticWindowHidden();
	}
}
