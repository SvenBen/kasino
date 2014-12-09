/*
 * mat_manipulator.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: sven
 */

#include <string>
#include <sstream>

#include "mat_manipulator.h"
#include "frame.h"
#include "windows.h"
#include "support.h"

const int MatManipulator::FONT_THICKNESS = 1;
const int MatManipulator::FONT_FACE = cv::FONT_HERSHEY_COMPLEX;
const int MatManipulator::FONT_LINE_TYPE = 8;

using namespace std;

MatManipulator::MatManipulator(Frame* frame, MainWindow* mainWindow) : TEXT_AREA_HD(cv::Point(1272, 0), cv::Point(1920, 300))
{
	this->mainWindow = mainWindow;
	this->frame = frame;
}

void MatManipulator::drawInfos()
{
	if (mainWindow->viewRoundNr())
	{
		textAddRoundNr();
	}

	if (mainWindow->viewCalculatedPerspective())
	{
		textAddPerspective();
	}

	if (mainWindow->viewTimeSinceRoundStart())
	{
		textAddTimeSinceRoundStart();
	}

	if (mainWindow->viewBallVelocity())
	{
		textAddBallRoundTime();
	}

	if (mainWindow->viewPlateVelocity())
	{
		textAddPlateRoundTime();
	}

	if (mainWindow->viewBallPosition())
	{
		textAddBallPosition();
	}

	if (mainWindow->viewNullPosition())
	{
		textAddNullPosition();
	}

	if (mainWindow->viewPerspectiveCalculation())
	{
		drawPerspectiveCalcInfos();
	}

	if (mainWindow->viewBallPosCalculation())
	{
		drawBallPosCalcInfos();
	}

	if (mainWindow->viewNullPosCalculation())
	{
		drawNullPosCalcInfos();
	}

	if (mainWindow->viewCrosshair())
	{
		drawCrosshair();
	}

	drawText();
}

void MatManipulator::drawCrosshair()
{
	// todo
}

void MatManipulator::textAddRoundNr()
{
	ostringstream oss;
	oss << "Runde Nr: ";
	if (frame->roundNr == -1) oss << "?"; else oss << frame->roundNr;
	infoText.push_back(oss.str());
}

void MatManipulator::textAddBallRoundTime()
{
	ostringstream oss;
	oss << "Ball Rundenzeit: ";
	if (frame->ballRoundTime == -1) oss << "?"; else oss << frame->ballRoundTime;
	infoText.push_back(oss.str());
}

void MatManipulator::textAddPlateRoundTime()
{
	ostringstream oss;
	oss << "Teller Rundenzeit: ";
	if (frame->plateRoundTime == -1) oss << "?"; else oss << frame->plateRoundTime;
	infoText.push_back(oss.str());
}

void MatManipulator::textAddPerspective()
{
	ostringstream oss;
	oss << "Perspektive: ";
	switch (frame->perspective)
	{
	case PERSPECTIVE_1:
		oss << 1;
		break;

	case PERSPECTIVE_2:
		oss << 2;
		break;

	case PERSPECTIVE_3:
		oss << 3;
		break;

	case PERSPECTIVE_4:
		oss << 4;
		break;

	case PERSPECTIVE_5:
		oss << 5;
		break;

	case PERSPECTIVE_OTHER:
		oss << "andere";
		break;

	case PERSPECTIVE_UNKNOWN:
		oss << "?";
		break;
	}

	infoText.push_back(oss.str());
}

void MatManipulator::textAddBallPosition()
{
	ostringstream oss;
	oss << "Ball Pos: ";
	oss << point2str(frame->ballPosition);
	infoText.push_back(oss.str());
}

void MatManipulator::textAddNullPosition()
{
	ostringstream oss;
	oss << "Null Pos: ";
	oss << point2str(frame->nullPosition);
	infoText.push_back(oss.str());
}

void MatManipulator::textAddTimeSinceRoundStart()
{
	ostringstream oss;
	oss <<  "Time: ";
	if (frame->timeSinceRoundStart == -1) oss << "?"; else oss << frame->timeSinceRoundStart;
	infoText.push_back(oss.str());
}

void MatManipulator::drawPerspectiveCalcInfos(/*todo*/)
{
	// todo
}

void MatManipulator::drawBallPosCalcInfos(/*todo*/)
{
	// todo
}

void MatManipulator::drawNullPosCalcInfos(/*todo*/)
{
	// todo
}

string MatManipulator::point2str(const cv::Point& p)
{
	if (p.x == numeric_limits<int>::infinity() || p.y == numeric_limits<int>::infinity())
	{
		return "(? ?)";
	}
	else
	{
		ostringstream oss;
		oss << "(" << p.x << " " << p.y << ")";
		return oss.str();
	}
}

void MatManipulator::drawText()
{
	double fontScale = 1.6 * Support::getScaleFactor(frame->quali); // Initialwert
	cv::Rect textBoundRect = Support::calcScaledRect(TEXT_AREA_HD, frame->quali);
	// rectangle(frame->mat, textBoundRect.tl(), textBoundRect.br(), cv::Scalar(255, 255, 255));
	cv::Point org = textBoundRect.tl();
	for(vector<string>::iterator it = infoText.begin(); it != infoText.end(); ++it)
	{
		org.y += 1.2 * cv::getTextSize(*it, FONT_FACE, fontScale, FONT_THICKNESS, NULL).height;
		cv::putText(frame->mat,
					*it,
					org,
					FONT_FACE,
					fontScale,
					cv::Scalar(255, 255, 255),
					FONT_THICKNESS,
					FONT_LINE_TYPE,
					false);
	}
}
