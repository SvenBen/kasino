
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
	// todo
}

void FrameWindow::cbNewFrame()
{
	// todo
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

MainWindow::MainWindow(Gui* gui) : Window(gui, MainWindow::WINDOW_NAME),
								   SETTINGS_FILE("gui/gui_settings.xml"),
								   selectedStreamQuality(QUALI_HD),
								   selectedServer(""),
								   selectedSlowmo(true),
								   streamControls(this),
								   viewOptionsControls(this),
								   newRoundDispatcher(sigc::mem_fun(*this, &MainWindow::cbNewRound)),
								   newCalculatedResultDispatcher(sigc::mem_fun(*this, &MainWindow::cbNewCalculatedResult)),
								   packetReceiverDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbPacketReceiverDestroyed)),
								   imageSaverDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbImageSaverDestroyed)),
								   videoWriterDestroyedDispatcher(sigc::mem_fun(*this, &MainWindow::cbVideoWriterDestroyed)),
								   perspectiveCalculatedDispatcher(sigc::mem_fun(*this, &MainWindow::cbPerspectiveCalculated))
{
	packetReceiver = NULL;
	setUpWindow();
	setUpCallbacks();
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
		if (settings[STR_SETTING_SLOWMO].type() == cv::FileNode::INT)
		{
			bool slowmo;
			settings[STR_SETTING_SLOWMO] >> slowmo;
			if (slowmo)
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
				break;

			case QUALI_HIGH:
				streamControls.quali_high->set_active();
				break;

			case QUALI_MEDIUM:
				streamControls.quali_medium->set_active();
				break;

			case QUALI_LOW:
				streamControls.quali_low->set_active();
				break;
			default:
				throw KasinoException(STR_ERR_READING_SETTINGS);
			}
		}

		if (settings[STR_SETTING_SERVER].type() == cv::FileNode::INT)
		{
			int serverIndex;
			settings[STR_SETTING_SERVER] >> serverIndex;
			streamControls.servers->set_active(serverIndex);
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

	view_calculated_perspective
	view_ball_position
	view_crosshair
	view_time_since_round_start
	view_ball_velocity
	view_plate_velocity
	view_perspective_calculation
	view_ball_path

	show_frame_window
	show_statistic_window*/
}

void MainWindow::saveSettings()
{
	cv::FileStorage settings(SETTINGS_FILE, cv::FileStorage::WRITE);
	if (settings.isOpened())
	{
		bool slowmo;
		if (streamControls.slowmotion_off->get_active())
		{
			slowmo = false;
		}
		else if (streamControls.slowmotion_on->get_active())
		{
			slowmo = true;
		}
		else
		{
			assert(0);
		}

		settings << STR_SETTING_SLOWMO << slowmo;

		StreamQuality quali;
		if (streamControls.quali_hd->get_active())
		{
			quali = QUALI_HD;
		}
		else if (streamControls.quali_high->get_active())
		{
			quali = QUALI_HIGH;
		}
		else if (streamControls.quali_medium->get_active())
		{
			quali = QUALI_MEDIUM;
		}
		else if (streamControls.quali_low->get_active())
		{
			quali = QUALI_LOW;
		}

		settings << STR_SETTING_QUALI << (int)quali;

		settings << STR_SETTING_SERVER << streamControls.servers->get_active_row_number();

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


const std::string StatisticWindow::GLADE_FILE = "gui/statistic_window.glade";
const std::string StatisticWindow::WINDOW_NAME = "statistic_window";

StatisticWindow::StatisticWindow(Gui* gui) :
		Window(gui, StatisticWindow::WINDOW_NAME)
{
	setUpCallbacks();
	// todo
}

void StatisticWindow::setUpCallbacks()
{
	// todo
}
