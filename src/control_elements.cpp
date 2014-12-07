
#include "control_elements.h"
#include "windows.h"
#include "gui.h"


ViewOptionsControls::ViewOptionsControls(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	view_frame_window = NULL;
	view_statistic_window = NULL;
	view_calculated_perspective = NULL;
	view_ball_position = NULL;
	view_null_position = NULL;
	view_crosshair = NULL;
	view_time_since_round_start = NULL;
	view_ball_velocity = NULL;
	view_plate_velocity = NULL;
	view_perspective_calculation = NULL;
	view_null_pos_calculation = NULL;
	view_ball_pos_calculation = NULL;
}

void ViewOptionsControls::setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder)
{
	builder->get_widget("view_frame_window", view_frame_window);
	builder->get_widget("view_statistic_window", view_statistic_window);
	builder->get_widget("view_calculated_perspective", view_calculated_perspective);
	builder->get_widget("view_ball_position", view_ball_position);
	builder->get_widget("view_null_position", view_null_position);
	builder->get_widget("view_crosshair", view_crosshair);
	builder->get_widget("view_time_since_round_start", view_time_since_round_start);
	builder->get_widget("view_ball_velocity", view_ball_velocity);
	builder->get_widget("view_plate_velocity", view_plate_velocity);
	builder->get_widget("view_perspective_calculation", view_perspective_calculation);
	builder->get_widget("view_null_pos_calculation", view_null_pos_calculation);
	builder->get_widget("view_ball_pos_calculation", view_ball_pos_calculation);
}

void ViewOptionsControls::setUpCallbacks()
{
	view_frame_window->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewFrameWindowToggled));
	view_statistic_window->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewStatisticWindowToggled));
	view_calculated_perspective->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewCalculatedPerspectiveToggled));
	view_ball_position->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewBallPositionToggled));
	view_null_position->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewNullPositionToggled));
	view_crosshair->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewCrosshairToggled));
	view_time_since_round_start->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewTimeSinceRoundStartToggled));
	view_ball_velocity->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewBallVelocityToggled));
	view_plate_velocity->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewPlateVelocityToggled));
	view_perspective_calculation->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewPerspectiveCalculationToggled));
	view_null_pos_calculation->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewNullPosCalculationToggled));
	view_ball_pos_calculation->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewBallPosCalculationToggled));
}

void ViewOptionsControls::cbViewFrameWindowToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewFrameWindowChecked = view_frame_window->get_active();
	mainWindow->frameWindow->setVisible(mainWindow->viewFrameWindowChecked);
	// todo
}

void ViewOptionsControls::cbViewStatisticWindowToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewStatisticWindowChecked = view_statistic_window->get_active();
	mainWindow->statisticWindow->setVisible(mainWindow->viewStatisticWindowChecked);
	// todo
}

void ViewOptionsControls::cbViewCalculatedPerspectiveToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewCalculatedPerspectiveChecked = view_calculated_perspective->get_active();
	// todo
}

void ViewOptionsControls::cbViewBallPositionToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewBallPositionChecked = view_ball_position->get_active();
	// todo
}

void ViewOptionsControls::cbViewNullPositionToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewNullPositionChecked = view_null_position->get_active();
	// todo
}

void ViewOptionsControls::cbViewCrosshairToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewCrosshairChecked = view_crosshair->get_active();
	// todo
}

void ViewOptionsControls::cbViewTimeSinceRoundStartToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewTimeSinceRoundStartChecked = view_time_since_round_start->get_active();
	// todo
}

void ViewOptionsControls::cbViewBallVelocityToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewBallVelocityChecked = view_ball_velocity->get_active();
	// todo
}

void ViewOptionsControls::cbViewPlateVelocityToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewPlateVelocityChecked = view_plate_velocity->get_active();
	// todo
}

void ViewOptionsControls::cbViewPerspectiveCalculationToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewPerspectiveCalculationChecked = view_perspective_calculation->get_active();
	// todo
}

void ViewOptionsControls::cbViewNullPosCalculationToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewNullPosCalculationChecked = view_null_pos_calculation->get_active();
	// todo
}

void ViewOptionsControls::cbViewBallPosCalculationToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewBallPosCalculationChecked = view_ball_pos_calculation->get_active();
	// todo
}


StreamControls::StreamControls(MainWindow* mainWindow) : mainWindow(mainWindow)
{
	// Initialisierung der Controls in MainWindow() -> setUpWindow() -> StreamControls::setUpControlElements()
	servers = NULL;
	quali_hd = NULL;
	quali_high = NULL;
	quali_medium = NULL;
	quali_low = NULL;
	slowmotion_on = NULL;
	slowmotion_off = NULL;
	btn_start_stream = NULL;
	btn_stop_stream = NULL;
}

void StreamControls::setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder)
{
	builder->get_widget("servers", servers);
	builder->get_widget("quali_hd", quali_hd);
	builder->get_widget("quali_high", quali_high);
	builder->get_widget("quali_medium", quali_medium);
	builder->get_widget("quali_low", quali_low);
	builder->get_widget("slowmotion_on", slowmotion_on);
	builder->get_widget("slowmotion_off", slowmotion_off);
	builder->get_widget("btn_start_stream", btn_start_stream);
	builder->get_widget("btn_stop_stream", btn_stop_stream);
}

void StreamControls::setUpCallbacks()
{
	servers->signal_changed().connect(sigc::mem_fun(*this, &StreamControls::cbServerChanged));
	quali_hd->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbQualiChanged));
	quali_high->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbQualiChanged));
	quali_medium->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbQualiChanged));
	quali_low->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbQualiChanged));
	slowmotion_on->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbSlowmoChanged));
	slowmotion_off->signal_toggled().connect(sigc::mem_fun(*this, &StreamControls::cbSlowmoChanged));
	btn_start_stream->signal_clicked().connect(sigc::mem_fun(*this, &StreamControls::cbStartStreamPressed));
	btn_stop_stream->signal_clicked().connect(sigc::mem_fun(*this, &StreamControls::cbStopStreamPressed));
}

void StreamControls::cbQualiChanged()
{
	if (quali_hd->get_active())		{ mainWindow->selectedStreamQuality = QUALI_HD; }
	if (quali_high->get_active())	{ mainWindow->selectedStreamQuality = QUALI_HIGH; }
	if (quali_medium->get_active())	{ mainWindow->selectedStreamQuality = QUALI_MEDIUM; }
	if (quali_low->get_active())	{ mainWindow->selectedStreamQuality = QUALI_LOW; }
}

void StreamControls::cbSlowmoChanged()
{
	if (slowmotion_on->get_active()) { mainWindow->selectedSlowmo = true; }
	if (slowmotion_off->get_active()) { mainWindow->selectedSlowmo = false; }
}

void StreamControls::cbStartStreamPressed()
{
	btn_start_stream->set_sensitive(false);
	btn_stop_stream->set_sensitive(true);
	mainWindow->createPacketReceiver();
}

void StreamControls::cbStopStreamPressed()
{
	mainWindow->destroyPacketReceiver();
	// die disable-Funktionen werden vom packetReceiverDestroyedDispatcher aufgerufen
}

void StreamControls::cbServerChanged()
{
	mainWindow->selectedServer = servers->get_active_text();
	mainWindow->selectedServerIndex = servers->get_active_row_number();
}
