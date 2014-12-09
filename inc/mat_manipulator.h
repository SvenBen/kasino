/*
 * mat_manipulator.h
 *
 *  Created on: Dec 9, 2014
 *      Author: sven
 */

#ifndef MAT_MANIPULATOR_H_
#define MAT_MANIPULATOR_H_

#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

class Frame;
class MainWindow;

class MatManipulator
{
private:
	static const int FONT_THICKNESS;
	static const int FONT_FACE;
	static const int FONT_LINE_TYPE;

	const cv::Rect TEXT_AREA_HD;
	Frame* frame;
	MainWindow* mainWindow;
	std::vector<std::string> infoText; // Jeder Eintrag eine Zeile

public:
	MatManipulator(Frame* frame, MainWindow* mainWindow);

	void drawInfos();

private:
	void drawCrosshair();
	void textAddRoundNr();
	void textAddBallRoundTime();
	void textAddPlateRoundTime();
	void textAddPerspective();
	void textAddBallPosition();
	void textAddNullPosition();
	void textAddTimeSinceRoundStart();
	void drawPerspectiveCalcInfos(/*todo*/);
	void drawBallPosCalcInfos(/*todo*/);
	void drawNullPosCalcInfos(/*todo*/);
	std::string point2str(const cv::Point& p);
	void drawText();
};

#endif /* MAT_MANIPULATOR_H_ */
