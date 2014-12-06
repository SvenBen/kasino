
#include "control_elements.h"
#include "windows.h"


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
	// todo
}

void ViewOptionsControls::setUpCallbacks()
{
	// todo
}


StreamControls::StreamControls(MainWindow* mainWindow) : mainWindow(mainWindow)
{
	// Initialisierung der Controls im Konstruktor von Window() -> Window::setUpWindow() -> StreamControls::setUpControlElements()
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
	// todo mainWindow->gui->
}

void StreamControls::cbStopStreamPressed()
{
	// todo
}

void StreamControls::cbServerChanged()
{
	mainWindow->selectedServer = servers->get_active_text();
}
