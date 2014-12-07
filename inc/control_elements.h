/*
 * control_elements.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef CONTROL_ELEMENTS_H_
#define CONTROL_ELEMENTS_H_

#include <gtkmm/filechooserbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>

class Window;
class MainWindow;

class ViewOptionsControls
{
	friend class MainWindow;

private:
	MainWindow* mainWindow;
	Gtk::CheckButton* view_frame_window;
	Gtk::CheckButton* view_statistic_window;
	Gtk::CheckButton* view_calculated_perspective;
	Gtk::CheckButton* view_ball_position;
	Gtk::CheckButton* view_null_position;
	Gtk::CheckButton* view_crosshair;
	Gtk::CheckButton* view_time_since_round_start;
	Gtk::CheckButton* view_ball_velocity;
	Gtk::CheckButton* view_plate_velocity;
	Gtk::CheckButton* view_perspective_calculation;
	Gtk::CheckButton* view_null_pos_calculation;
	Gtk::CheckButton* view_ball_pos_calculation;

	ViewOptionsControls(MainWindow* mainWindow);
	void setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder);
	void setUpCallbacks();

	void cbViewFrameWindowToggled();
	void cbViewStatisticWindowToggled();
	void cbViewCalculatedPerspectiveToggled();
	void cbViewBallPositionToggled();
	void cbViewNullPositionToggled();
	void cbViewCrosshairToggled();
	void cbViewTimeSinceRoundStartToggled();
	void cbViewBallVelocityToggled();
	void cbViewPlateVelocityToggled();
	void cbViewPerspectiveCalculationToggled();
	void cbViewNullPosCalculationToggled();
	void cbViewBallPosCalculationToggled();
};

class StreamControls
{
	friend class MainWindow;

private:
	MainWindow* mainWindow;
	Gtk::ComboBoxText* servers;
	Gtk::RadioButton* quali_hd;
	Gtk::RadioButton* quali_high;
	Gtk::RadioButton* quali_medium;
	Gtk::RadioButton* quali_low;
	Gtk::RadioButton* slowmotion_on;
	Gtk::RadioButton* slowmotion_off;
	Gtk::Button* btn_start_stream;
	Gtk::Button* btn_stop_stream;

	StreamControls(MainWindow* mainWindow);
	void setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder);
	void setUpCallbacks();
	void cbQualiChanged();
	void cbSlowmoChanged();
	void cbStartStreamPressed();
	void cbStopStreamPressed();
	void cbServerChanged();
};


class RecordControls
{
	friend class MainWindow;

private:
	MainWindow* mainWindow;
	Gtk::FileChooserButton* video_record_path;
	Gtk::Button* video_record_start;
	Gtk::Button* video_record_stop;
	Gtk::FileChooserButton* image_record_path;
	Gtk::Button* image_record_start;
	Gtk::Button* image_record_stop;


	RecordControls(MainWindow* mainWindow);
	void setUpControlElements(const Glib::RefPtr<Gtk::Builder>& builder);
	void setUpCallbacks();
	void cbVideoRecordPathSet();
	void cbVideoRecordStartClicked();
	void cbVideoRecordStopClicked();
	void cbImageRecordPathSet();
	void cbImageRecordStartClicked();
	void cbImageRecordStopClicked();
};


#endif /* CONTROL_ELEMENTS_H_ */
