/*
 * image_saver.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include "image_saver.h"
#include "windows.h"

ImageSaver::ImageSaver(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	// TODO Auto-generated constructor stub

}

ImageSaver::~ImageSaver()
{
	mainWindow->notifyImageSaverDestroyed();
	// TODO Auto-generated destructor stub
}

