/*
 * video_writer.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_

class MainWindow;

class VideoWriter
{
private:
	MainWindow* mainWindow;
	// todo
public:
	VideoWriter(MainWindow* mainWindow);
	virtual ~VideoWriter();
};

#endif /* VIDEO_WRITER_H_ */
