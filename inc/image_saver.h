/*
 * image_saver.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef IMAGE_SAVER_H_
#define IMAGE_SAVER_H_

class MainWindow;

class ImageSaver
{
private:
	MainWindow* mainWindow;
	// todo
public:
	ImageSaver(MainWindow* mainWindow);
	virtual ~ImageSaver();
};

#endif /* IMAGE_SAVER_H_ */
