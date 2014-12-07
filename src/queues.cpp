
#include <opencv2/core/core.hpp>
#include <string>

extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavutil/avutil.h>
}

#include "round.h"
#include "frame.h"
#include "logger.h"
#include "queues.h"


void deletePacketFreeFunc(gpointer data)
{
	delete (AVPacket*)data;
}

void deleteStringFreeFunc(gpointer data)
{
	delete (std::string*)data;
}
