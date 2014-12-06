
#include <gtkmm/window.h>

#include "windows.h"


Window::Window(Gui* gui, const std::string& windowName, const std::string& glade_file) :
			WINDOW_NAME(windowName)
{
	this->gui = gui;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(glade_file);
	setUpWindow(builder);
	setUpCallbacks();
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

void Window::setUpCallbacks()
{
	// wird in der abgeleiteten Klasse implementiert
}


const std::string FrameWindow::GLADE_FILE = "gui/frame_window.glade";
const std::string FrameWindow::WINDOW_NAME = "frame_window";

FrameWindow::FrameWindow(Gui* gui) :
		Window(gui, FrameWindow::WINDOW_NAME, FrameWindow::GLADE_FILE)
{
	// todo
}


const std::string StatusWindow::GLADE_FILE = "gui/status_window.glade";
const std::string StatusWindow::WINDOW_NAME = "status_window";

StatusWindow::StatusWindow(Gui* gui) :
		Window(gui, StatusWindow::WINDOW_NAME, StatusWindow::GLADE_FILE)
{
	// todo
}


const std::string MainWindow::GLADE_FILE = "gui/main_window.glade";
const std::string MainWindow::WINDOW_NAME = "main_window";

MainWindow::MainWindow(Gui* gui) : Window(gui, MainWindow::WINDOW_NAME, MainWindow::GLADE_FILE),
								   SAVE_SETTINGS_FILE("guiSettings.xml"),
								   selectedStreamQuality(QUALI_HD),
								   selectedServer(""),
								   selectedSlowmo(true),
								   streamControls(this),
								   viewOptionsControls(this)
{
}

MainWindow::~MainWindow()
{
	saveDefaultSettings();
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

void MainWindow::setUpWindow(const Glib::RefPtr<Gtk::Builder>& builder)
{
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

void MainWindow::loadDefaultSettings()
{
	// todo
}

void MainWindow::saveDefaultSettings()
{
	// todo
}

void MainWindow::resetRoundObservations()
{
	// todo
}

const std::string StatisticWindow::GLADE_FILE = "gui/statistic_window.glade";
const std::string StatisticWindow::WINDOW_NAME = "statistic_window";

StatisticWindow::StatisticWindow(Gui* gui) :
		Window(gui, StatisticWindow::WINDOW_NAME, StatisticWindow::GLADE_FILE)
{
	// todo
}
