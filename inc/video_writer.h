/*
 * video_writer.h
 *
 *  Created on: Dec 7, 2014
 *      Author: sven
 */

#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_

#include <opencv2/highgui/highgui.hpp>

#include "thread.h"
#include "frame.h"
#include "queue_holder.h"

class FrameAnalysator;
class MainWindow;

class VideoWriter : public Thread, public QueueHolder<Frame*>
{
private:
	MainWindow* mainWindow;
	FrameAnalysator* frameAnalysator;
	std::string savePath;
	cv::VideoWriter videoWriter;

public:
	VideoWriter(MainWindow* mainWindow,
				FrameAnalysator* frameAnalysator,
				const std::string & savePath);
	virtual ~VideoWriter();

private:
	void openVideoFile(int roundNr, const cv::Size2i& size);
	void closeVideoFile();
	virtual void threadFunc();
};

#endif /* VIDEO_WRITER_H_ */
