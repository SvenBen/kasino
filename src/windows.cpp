
#include <gtkmm/window.h>
#include <assert.h>

#include "windows.h"
#include "macros.h"
#include "kasino_exception.h"
#include "strings.h"

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
	setUpWindow();
	setUpCallbacks();
	// todo
}

void FrameWindow::setVisible(bool v)
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
	// todo
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
		Window(gui, StatusWindow::WINDOW_NAME)
{
	// todo
}


const std::string MainWindow::GLADE_FILE = "gui/main_window.glade";
const std::string MainWindow::WINDOW_NAME = "main_window";

MainWindow::MainWindow(Gui* gui, FrameWindow* fw, StatisticWindow* sw) :
		Window(gui, MainWindow::WINDOW_NAME),
	    SETTINGS_FILE("gui/gui_settings.xml"),
	    streamControls(this),
	    viewOptionsControls(this),
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
	statisticWindow = sw;
	frameWindow = fw;
	setUpWindow();
	setUpCallbacks();

	selectedStreamQuality = QUALI_HD;
	selectedServerIndex = streamControls.servers->get_active_row_number();
	selectedServer = streamControls.servers->get_active_text();
	selectedSlowmo = true;
	viewFrameWindowChecked = false;
	viewStatisticWindowChecked = false;
	viewCalculatedPerspectiveChecked = false;
	viewBallPositionChecked = false;
	viewNullPositionChecked = false;
	viewCrosshairChecked = false;
	viewTimeSinceRoundStartChecked = false;
	viewBallVelocityChecked = false;
	viewPlateVelocityChecked = false;
	viewPerspectiveCalculationChecked = false;
	viewNullPosCalculationChecked = false;
	viewBallPosCalculationChecked = false;

	frameWindow->setVisible(viewFrameWindowChecked);
	statisticWindow->setVisible(viewStatisticWindowChecked);

	try
	{
		loadSettings();
	}
	catch (KasinoException& e)
	{
		// todo log message
	}
}

MainWindow::~MainWindow()
{
	SAFE_DELETE_NULL(packetReceiver)
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

const SharedUserObservationsPtr MainWindow::getUserObservations()
{
	Glib::Threads::Mutex::Lock lock(userObsMutex);
	return userObservations;
}

void MainWindow::setUpWindow()
{
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_FILE);
	Window::setUpWindow(builder);

	streamControls.setUpControlElements(builder);
	viewOptionsControls.setUpControlElements(builder);
	// todo
}

void MainWindow::setUpCallbacks()
{
	streamControls.setUpCallbacks();
	viewOptionsControls.setUpCallbacks();
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

		if (settings[STR_SETTING_SERVER].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_SERVER] >> selectedServerIndex;
			streamControls.servers->set_active(selectedServerIndex);
			selectedServer = streamControls.servers->get_active_text();
		}

		// ViewOptions Settings
		if (settings[STR_SETTING_VIEW_FRAME_WINDOW].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_FRAME_WINDOW] >> viewFrameWindowChecked;
			viewOptionsControls.view_frame_window->set_active(viewFrameWindowChecked);
			frameWindow->setVisible(viewFrameWindowChecked);
		}
		if (settings[STR_SETTING_VIEW_STATISTIC_WINDOW].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_STATISTIC_WINDOW] >> viewStatisticWindowChecked;
			viewOptionsControls.view_statistic_window->set_active(viewStatisticWindowChecked);
			statisticWindow->setVisible(viewStatisticWindowChecked);
		}
		if (settings[STR_SETTING_VIEW_CALCULATED_PERSPECTIVE].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_CALCULATED_PERSPECTIVE] >> viewCalculatedPerspectiveChecked;
			viewOptionsControls.view_calculated_perspective->set_active(viewCalculatedPerspectiveChecked);
		}
		if (settings[STR_SETTING_VIEW_BALL_POSITION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_POSITION] >> viewBallPositionChecked;
			viewOptionsControls.view_ball_position->set_active(viewBallPositionChecked);
		}
		if (settings[STR_SETTING_VIEW_NULL_POSITION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_NULL_POSITION] >> viewNullPositionChecked;
			viewOptionsControls.view_null_position->set_active(viewNullPositionChecked);
		}
		if (settings[STR_SETTING_VIEW_CROSSHAIR].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_CROSSHAIR] >> viewCrosshairChecked;
			viewOptionsControls.view_crosshair->set_active(viewCrosshairChecked);
		}
		if (settings[STR_SETTING_VIEW_TIME_SINCE_ROUND_START].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_TIME_SINCE_ROUND_START] >> viewTimeSinceRoundStartChecked;
			viewOptionsControls.view_time_since_round_start->set_active(viewTimeSinceRoundStartChecked);
		}
		if (settings[STR_SETTING_VIEW_BALL_VELOCITY].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_VELOCITY] >> viewBallVelocityChecked;
			viewOptionsControls.view_ball_velocity->set_active(viewBallVelocityChecked);
		}
		if (settings[STR_SETTING_VIEW_PLATE_VELOCITY].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_PLATE_VELOCITY] >> viewPlateVelocityChecked;
			viewOptionsControls.view_plate_velocity->set_active(viewPlateVelocityChecked);
		}
		if (settings[STR_SETTING_VIEW_PERSPECTIVE_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_PERSPECTIVE_CALCULATION] >> viewPerspectiveCalculationChecked;
			viewOptionsControls.view_perspective_calculation->set_active(viewPerspectiveCalculationChecked);
		}
		if (settings[STR_SETTING_VIEW_NULL_POS_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_NULL_POS_CALCULATION] >> viewNullPosCalculationChecked;
			viewOptionsControls.view_null_pos_calculation->set_active(viewNullPosCalculationChecked);
		}
		if (settings[STR_SETTING_VIEW_BALL_POS_CALCULATION].type() == cv::FileNode::INT)
		{
			settings[STR_SETTING_VIEW_BALL_POS_CALCULATION] >> viewBallPosCalculationChecked;
			viewOptionsControls.view_ball_pos_calculation->set_active(viewBallPosCalculationChecked);
		}

		// todo
	}
	else
	{
		throw KasinoException(STR_CANNOT_OPEN_FILE(SETTINGS_FILE));
	}

	settings.release();

	/*
	 * analyze
	path_round_log_file

	video_record_path
	image_record_path

	show_frame_window
	show_statistic_window*/
}

void MainWindow::saveSettings()
{
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
		settings << STR_SETTING_VIEW_BALL_POSITION << viewBallPositionChecked;
		settings << STR_SETTING_VIEW_NULL_POSITION << viewNullPositionChecked;
		settings << STR_SETTING_VIEW_CROSSHAIR << viewCrosshairChecked;
		settings << STR_SETTING_VIEW_TIME_SINCE_ROUND_START << viewTimeSinceRoundStartChecked;
		settings << STR_SETTING_VIEW_BALL_VELOCITY << viewBallVelocityChecked;
		settings << STR_SETTING_VIEW_PLATE_VELOCITY << viewPlateVelocityChecked;
		settings << STR_SETTING_VIEW_PERSPECTIVE_CALCULATION << viewPerspectiveCalculationChecked;
		settings << STR_SETTING_VIEW_NULL_POS_CALCULATION << viewNullPosCalculationChecked;
		settings << STR_SETTING_VIEW_BALL_POS_CALCULATION << viewBallPosCalculationChecked;

		// todo
	}
	else
	{
		throw KasinoException(STR_CANNOT_OPEN_FILE(SETTINGS_FILE));
	}

	settings.release();

	/*
	 * analyze
	path_round_log_file

	video_record_path
	image_record_path

	view_calculated_perspective
	view_ball_position
	view_crosshair
	view_time_since_round_start
	view_ball_velocity
	view_plate_velocity
	view_perspective_calculation
	view_ball_path

	show_frame_window
	show_statistic_window
	*/
}

void MainWindow::resetUserObservations()
{
	// todo
}

void MainWindow::cbNewRound()
{
	// todo
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
	// todo
}

void MainWindow::cbVideoWriterDestroyed()
{
	// todo
}

void MainWindow::cbPerspectiveCalculated()
{
	// todo
}

void MainWindow::createPacketReceiver()
{
	packetReceiver = new PacketReceiver(this);
	if (packetReceiver == NULL)
	{
		throw KasinoException(STR_NOT_ENOUGH_SPACE);
	}
}

void MainWindow::destroyPacketReceiver()
{
	SAFE_DELETE_NULL(packetReceiver)
}

void MainWindow::notifyPackerReceiverDestroyed()
{
	packetReceiverDestroyedDispatcher.notify();
}

void MainWindow::notifyFrameWindowHidden()
{
	frameWindowHiddenDispatcher.notify();
}

void MainWindow::notifyStatisticWindowHidden()
{
	statisticWindowHiddenDispatcher.notify();
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
