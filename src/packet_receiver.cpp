/*
 * packet_receiver.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#include "packet_receiver.h"
#include "kasino_exception.h"
#include "windows.h"
#include "kasino_strings.h"
#include "frame.h"

Stream::Stream(StreamQuality quali, bool withSlowmo, const std::string& serverIP)
{
	this->quali = quali;
	withSlowmotion = withSlowmo;
	this->serverIP = serverIP;
}

std::string Stream::getStreamURL() const
{
	std::string strCamQuali = "immersive_";
	if (!withSlowmotion)
	{
		strCamQuali += "cam5_";
	}
	switch (quali)
	{
	case QUALI_HD:
		strCamQuali += "hd";
		break;

	case QUALI_HIGH:
		strCamQuali += "hi";
		break;

	case QUALI_MEDIUM:
		strCamQuali += "med";
		break;

	case QUALI_LOW:
		strCamQuali += "low";
		break;
	}

	return "rtmp://" + serverIP + ":1935/casino/" + strCamQuali + " live=1";
}

PacketReceiver::PacketReceiver(const Stream& stream,
							   MainWindow* mainWindow,
							   FrameAnalysator* analysator) :
		QueueUser(analysator),
		stream(stream),
		FRAME_FORMAT_CV(AV_PIX_FMT_BGR24)
{
	codecCtx = NULL;
	formatCtx = NULL;
	imgConverter = NULL;
	frameReceived = NULL;
	frameBGR = NULL;
	frameBGRBuffer = NULL;
	this->mainWindow = mainWindow;

	thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &PacketReceiver::threadFunc));
	// create() wirft Glib::Exception
}

PacketReceiver::~PacketReceiver()
{
	quit = true;
	if (thread != NULL)
	{
		thread->join();
	}

	exit();
	mainWindow->notifyPacketReceiverDestroyed();
	mainWindow->log("Packet Receiver zerstört");
}

void PacketReceiver::frame2mat(const AVFrame& frameBGR, cv::Mat& matBGR)
{
	matBGR.create(codecCtx->height, codecCtx->width, CV_8UC(3));
	for (int y = 0; y < codecCtx->height; y++)
	{
		for (int x = 0; x < codecCtx->width; x++)
		{
			matBGR.at<cv::Vec3b>(y, x)[0] = frameBGR.data[0][y * frameBGR.linesize[0] + x * 3 + 0];
			matBGR.at<cv::Vec3b>(y, x)[1] = frameBGR.data[0][y * frameBGR.linesize[0] + x * 3 + 1];
			matBGR.at<cv::Vec3b>(y, x)[2] = frameBGR.data[0][y * frameBGR.linesize[0] + x * 3 + 2];
		}
	}
}

void PacketReceiver::threadFunc()
{
	init();
	mainWindow->log("Empfange Pakete…");

	int error;
	int gotPicture = 0;
	AVPacket packet;
	while (!quit)
	{
		try
		{
			packet = { 0 };
			av_init_packet(&packet);
			error = av_read_frame(formatCtx, &packet);
			if (error < 0)
			{
				throw KasinoException(avErr2Str(error));
			}

			if (packet.stream_index == videoStreamNr)
			{
				error = avcodec_decode_video2(codecCtx,
											  frameReceived,
											  &gotPicture,
											  &packet);
				if (error < 0)
				{
					throw KasinoException(avErr2Str(error));
				}

				if (gotPicture != 0)
				{
					sws_scale(imgConverter,
							  ((AVPicture*)frameReceived)->data,
							  ((AVPicture*)frameReceived)->linesize,
							  0,
							  codecCtx->height,
							  ((AVPicture *)frameBGR)->data,
							  ((AVPicture *)frameBGR)->linesize);

					cv::Mat imgCv;
					frame2mat(*frameBGR, imgCv);
					Frame* frame = new Frame(imgCv);
					if (frame == NULL)
					{
						throw NotEnoughSpaceException();
					}

					frame->pts = 0; // todo welchen Wert hier reinziehen?
					push(frame);
				}
			}
		}
		catch(KasinoException& e)
		{
			mainWindow->log(e.what(), ERROR);
		}

		av_free_packet(&packet);
	}
}

char* const PacketReceiver::avErr2Str(const int error)
{
	static char error_buffer[255];
	av_strerror(error, error_buffer, sizeof(error_buffer));
	return error_buffer;
}

void PacketReceiver::init()
{
	initAVLibs();
	openStream();
	createPictureConverter();
	createFrames();
}

void PacketReceiver::exit()
{
	destroyFrames();
	destroyPictureConverter();
	closeStream();
	exitAVLibs();
}

void PacketReceiver::initAVLibs()
{
	av_register_all();
	avcodec_register_all();
	avformat_network_init();
}

void PacketReceiver::exitAVLibs()
{
	avformat_network_deinit();
}

void PacketReceiver::openStream()
{
	int error;
	// Open input stream
	error = avformat_open_input(&formatCtx, stream.getStreamURL().c_str(), NULL, NULL);
	if (error != 0)
	{
		throw KasinoException(avErr2Str(error));
	}

	mainWindow->log("Stream geoeffnet", INFO);

	// Retrieve stream information
	error = avformat_find_stream_info(formatCtx, NULL);
	if(error < 0)
	{
		exit();
		throw KasinoException(avErr2Str(error));
	}

	// Find the first video stream
	videoStreamNr = -1;
	for (unsigned int i = 0; i < formatCtx->nb_streams; i++)
	{
		if (formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStreamNr = i;
			break;
		}
	}

	if (videoStreamNr == -1)
	{
		exit();
		throw KasinoException("Cannot find video stream");
	}

	// Get a pointer to the codec context for the video stream
	codecCtx = formatCtx->streams[videoStreamNr]->codec;

	// Find the decoder for the video stream
	AVCodec *codec = avcodec_find_decoder(codecCtx->codec_id);
	if(codec == NULL)
	{
		exit();
		throw KasinoException("Codec nicht gefunden");
	}

	// Open codec
	error = avcodec_open2(codecCtx, codec, NULL);
	if (error != 0)
	{
		exit();
		throw KasinoException(avErr2Str(error));
	}
}

void PacketReceiver::closeStream()
{
	if (codecCtx != NULL)
	{
		avcodec_close(codecCtx);
	}

	if (formatCtx != NULL)
	{
		avformat_close_input(&formatCtx);
	}

	mainWindow->log("Stream geschlossen", INFO);
}

void PacketReceiver::createPictureConverter()
{
	imgConverter = sws_getCachedContext(imgConverter,
										codecCtx->width,
										codecCtx->height,
										codecCtx->pix_fmt,
										codecCtx->width,
										codecCtx->height,
										FRAME_FORMAT_CV,
										SWS_BICUBIC,
										NULL,
										NULL,
										NULL);
	if (imgConverter == NULL)
	{
		exit();
		throw KasinoException("Cannot initialize the convert context");
	}
}

void PacketReceiver::destroyPictureConverter()
{
	sws_freeContext(imgConverter);
	imgConverter = NULL;
}

void PacketReceiver::createFrames()
{
	frameReceived = avcodec_alloc_frame(); // av_frame_alloc()
	frameBGR = avcodec_alloc_frame(); // av_frame_alloc()
	if (frameReceived == NULL || frameBGR == NULL)
	{
		exit();
		throw NotEnoughSpaceException();
	}

	int numBytes = avpicture_get_size(FRAME_FORMAT_CV, codecCtx->width, codecCtx->height);
	frameBGRBuffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
	if (frameBGRBuffer == NULL)
	{
		exit();
		throw NotEnoughSpaceException();
	}

	int error = avpicture_fill((AVPicture *) frameBGR,
							   frameBGRBuffer,
							   FRAME_FORMAT_CV,
							   codecCtx->width,
							   codecCtx->height);
	if (error < 0)
	{
		exit();
		throw KasinoException(avErr2Str(error));
	}
}

void PacketReceiver::destroyFrames()
{
	av_free(frameBGRBuffer);
	frameBGRBuffer = NULL;

	avcodec_free_frame(&frameReceived);
	//av_frame_free(&frameReceived);

	avcodec_free_frame(&frameBGR);
}
