
#include "control_elements.h"
#include "windows.h"
#include "gui.h"
#include "user_observations.h"


ViewOptionsControls::ViewOptionsControls(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	view_frame_window = NULL;
	view_statistic_window = NULL;
	view_calculated_perspective = NULL;
	view_round_nr = NULL;
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
	builder->get_widget("view_round_nr", view_round_nr);
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
	view_round_nr->signal_toggled().connect(sigc::mem_fun(*this, &ViewOptionsControls::cbViewRoundNrToggled));
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

void ViewOptionsControls::cbViewRoundNrToggled()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->viewRoundNrChecked = view_round_nr->get_active();
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


StreamControls::StreamControls(MainWindow* mainWindow)
{
	// Initialisierung der Controls in MainWindow() -> setUpWindow() -> StreamControls::setUpControlElements()
	this->mainWindow = mainWindow;
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
	btn_stop_stream->set_sensitive(false);
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

RecordControls::RecordControls(MainWindow* mainWindow)
{
	// Initialisierung der Controls in MainWindow() -> setUpWindow() -> RecordControls::setUpControlElements()
	this->mainWindow = mainWindow;
	video_record_path = NULL;
	video_record_start = NULL;
	video_record_stop = NULL;
	image_record_path = NULL;
	image_record_start = NULL;
	image_record_stop = NULL;
}

void RecordControls::setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder)
{
	builder->get_widget("video_record_path", video_record_path);
	builder->get_widget("video_record_start", video_record_start);
	builder->get_widget("video_record_stop", video_record_stop);
	builder->get_widget("image_record_path", image_record_path);
	builder->get_widget("image_record_start", image_record_start);
	builder->get_widget("image_record_stop", image_record_stop);

	video_record_stop->set_sensitive(false);
	image_record_stop->set_sensitive(false);
}

void RecordControls::setUpCallbacks()
{
	video_record_path->signal_file_set().connect(sigc::mem_fun(*this, &RecordControls::cbVideoRecordPathSet));
	video_record_start->signal_clicked().connect(sigc::mem_fun(*this, &RecordControls::cbVideoRecordStartClicked));
	video_record_stop->signal_clicked().connect(sigc::mem_fun(*this, &RecordControls::cbVideoRecordStopClicked));
	image_record_path->signal_file_set().connect(sigc::mem_fun(*this, &RecordControls::cbImageRecordPathSet));
	image_record_start->signal_clicked().connect(sigc::mem_fun(*this, &RecordControls::cbImageRecordStartClicked));
	image_record_stop->signal_clicked().connect(sigc::mem_fun(*this, &RecordControls::cbImageRecordStopClicked));
}

void RecordControls::cbVideoRecordPathSet()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->videoRecordPath = video_record_path->get_filename();
}

void RecordControls::cbVideoRecordStartClicked()
{
	video_record_start->set_sensitive(false);
	video_record_stop->set_sensitive(true);
	mainWindow->createVideoWriter();
}

void RecordControls::cbVideoRecordStopClicked()
{
	mainWindow->destroyVideoWriter();
	// die disable-Funktionen werden vom videoWriterDestroyedDispatcher aufgerufen
}

void RecordControls::cbImageRecordPathSet()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->imageRecordPath = image_record_path->get_filename();
}

void RecordControls::cbImageRecordStartClicked()
{
	image_record_start->set_sensitive(false);
	image_record_stop->set_sensitive(true);
	mainWindow->createImageSaver();
}

void RecordControls::cbImageRecordStopClicked()
{
	mainWindow->destroyImageSaver();
	// die disable-Funktionen werden vom imageSaverDestroyedDispatcher aufgerufen
}


DataRecordControls::DataRecordControls(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	analyze = NULL;
	record_round = NULL;
	path_round_log_file = NULL;
	round_nr = NULL;
	perspective_nr = NULL;
	rhombe_dont_know = NULL;
	rhombe_n = NULL;
	rhombe_no = NULL;
	rhombe_o = NULL;
	rhombe_so = NULL;
	rhombe_s = NULL;
	rhombe_sw = NULL;
	rhombe_w = NULL;
	rhombe_nw = NULL;
	ball_direction_dont_know = NULL;
	ball_direction_clockwise = NULL;
	ball_direction_counterclockwise = NULL;
	rhombe_hit_dont_know = NULL;
	rhombe_hit_hard = NULL;
	rhombe_hit_soft = NULL;
	result_number = NULL;
	btn_absage = NULL;
	time_absage = NULL;
	btn_delete_last_round = NULL;
}
void DataRecordControls::setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder)
{
	builder->get_widget("analyze", analyze);
	builder->get_widget("record_round", record_round);
	builder->get_widget("path_round_log_file", path_round_log_file);
	builder->get_widget("round_nr", round_nr);
	builder->get_widget("perspective_nr", perspective_nr);
	builder->get_widget("rhombe_dont_know", rhombe_dont_know);
	builder->get_widget("rhombe_n", rhombe_n);
	builder->get_widget("rhombe_no", rhombe_no);
	builder->get_widget("rhombe_o", rhombe_o);
	builder->get_widget("rhombe_so", rhombe_so);
	builder->get_widget("rhombe_s", rhombe_s);
	builder->get_widget("rhombe_sw", rhombe_sw);
	builder->get_widget("rhombe_w", rhombe_w);
	builder->get_widget("rhombe_nw", rhombe_nw);
	builder->get_widget("ball_direction_dont_know", ball_direction_dont_know);
	builder->get_widget("ball_direction_clockwise", ball_direction_clockwise);
	builder->get_widget("ball_direction_counterclockwise", ball_direction_counterclockwise);
	builder->get_widget("rhombe_hit_dont_know", rhombe_hit_dont_know);
	builder->get_widget("rhombe_hit_hard", rhombe_hit_hard);
	builder->get_widget("rhombe_hit_soft", rhombe_hit_soft);
	builder->get_widget("result_number", result_number);
	builder->get_widget("btn_absage", btn_absage);
	builder->get_widget("time_absage", time_absage);
	builder->get_widget("btn_delete_last_round", btn_delete_last_round);
}

void DataRecordControls::setUpCallbacks()
{
	analyze->property_active().signal_changed().connect(sigc::mem_fun(*this, &DataRecordControls::cbAnalyzeActivated));
	record_round->property_active().signal_changed().connect(sigc::mem_fun(*this, &DataRecordControls::cbRecordRoundActivated));
	path_round_log_file->signal_file_set().connect(sigc::mem_fun(*this, &DataRecordControls::cbPathRoundLogFilePathSet));
	rhombe_dont_know->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_n->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_no->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_o->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_so->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_s->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_sw->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_w->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	rhombe_nw->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeChanged));
	ball_direction_dont_know->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbBallDirectionChanged));
	ball_direction_clockwise->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbBallDirectionChanged));
	ball_direction_counterclockwise->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbBallDirectionChanged));
	rhombe_hit_dont_know->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeHitChanged));
	rhombe_hit_hard->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeHitChanged));
	rhombe_hit_soft->signal_toggled().connect(sigc::mem_fun(*this, &DataRecordControls::cbRhombeHitChanged));
	result_number->signal_value_changed().connect(sigc::mem_fun(*this, &DataRecordControls::cbResultNumberValueChanged));
	btn_absage->signal_clicked().connect(sigc::mem_fun(*this, &DataRecordControls::cbAbsageClicked));
	btn_delete_last_round->signal_clicked().connect(sigc::mem_fun(*this, &DataRecordControls::cbDeleteLastRoundClicked));
}

void DataRecordControls::cbAnalyzeActivated()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->analyze = analyze->get_active();
	// todo
}

void DataRecordControls::cbRecordRoundActivated()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->recordRound = record_round->get_active();
	// todo
}

void DataRecordControls::cbPathRoundLogFilePathSet()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->pathRoundLogFile = path_round_log_file->get_filename();
	// todo
}

void DataRecordControls::cbRhombeChanged()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	if (rhombe_dont_know->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_DONT_KNOW;
	}
	else if (rhombe_n->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_N;
	}
	else if (rhombe_no->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_NO;
	}
	else if (rhombe_o->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_O;
	}
	else if (rhombe_so->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_SO;
	}
	else if (rhombe_s->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_S;
	}
	else if (rhombe_sw->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_SW;
	}
	else if (rhombe_w->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_W;
	}
	else if (rhombe_nw->get_active())
	{
		mainWindow->userObservations.rhombe = RHOMBE_NW;
	}
}

void DataRecordControls::cbBallDirectionChanged()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	if (ball_direction_dont_know->get_active())
	{
		mainWindow->userObservations.ballDirection = BD_DONT_KNOW;
	}
	else if (ball_direction_clockwise->get_active())
	{
		mainWindow->userObservations.ballDirection = BD_CLOCKWISE;
	}
	else if (ball_direction_counterclockwise->get_active())
	{
		mainWindow->userObservations.ballDirection = BD_COUNTERCLOCKWISE;
	}
}

void DataRecordControls::cbRhombeHitChanged()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	if (rhombe_hit_dont_know->get_active())
	{
		mainWindow->userObservations.hardness = H_DONT_KNOW;
	}
	else if (rhombe_hit_hard->get_active())
	{
		mainWindow->userObservations.hardness = H_HARD;
	}
	else if (rhombe_hit_soft->get_active())
	{
		mainWindow->userObservations.hardness = H_SOFT;
	}
}

void DataRecordControls::cbResultNumberValueChanged()
{
	Glib::Threads::Mutex::Lock lock(mainWindow->controlValueMutex);
	mainWindow->userObservations.resultNumber = result_number->get_value_as_int();
}

void DataRecordControls::cbAbsageClicked()
{
	// todo
}

void DataRecordControls::cbDeleteLastRoundClicked()
{
	// todo
}
