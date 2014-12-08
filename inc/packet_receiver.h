/*
 * packet_receiver.h
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#ifndef PACKET_RECEIVER_H_
#define PACKET_RECEIVER_H_

#include <opencv2/core/core.hpp>

extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
}

#include "thread.h"
#include "queues.h"
#include "enum_types.h"
#include "frame_analysator.h"


class MainWindow;

class Stream
{
private:
	StreamQuality quali;
	bool withSlowmotion;
	std::string serverIP;

public:
	Stream(StreamQuality quali, bool withSlowmo, const std::string& serverIP);
	std::string getStreamURL() const;
};

class PacketReceiver : public Thread, public QueueUser<cv::Mat*>
{
private:
	MainWindow* mainWindow;
	Stream stream;
	AVFormatContext *formatCtx;
	AVCodecContext *codecCtx;
	int videoStreamNr;
	SwsContext* imgConverter;
	AVFrame* frameReceived;
	AVFrame* frameBGR;
	uint8_t* frameBGRBuffer;
	const AVPixelFormat FRAME_FORMAT_CV;

	// todo
public:
	PacketReceiver(const Stream& stream, MainWindow* mainWindow, FrameAnalysator* analysator);
	virtual ~PacketReceiver();

private:
	void frame2mat(const AVFrame& frameBGR, cv::Mat& matBGR);
	virtual void threadFunc();
	char* const avErr2Str(const int error);
	void init();
	void exit();
	void initAVLibs();
	void exitAVLibs();
	void openStream();
	void closeStream();
	void createPictureConverter();
	void destroyPictureConverter();
	void createFrames();
	void destroyFrames();
	std::string getStreamUrl();
};

#endif /* PACKET_RECEIVER_H_ */
