/*
 * video_writer.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#include "video_writer.h"
#include "windows.h"

VideoWriter::VideoWriter(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	// todo
}

VideoWriter::~VideoWriter()
{
	mainWindow->notifyVideoWriterDestroyed();
	// todo
}

