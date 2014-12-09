
#include <opencv2/core/core.hpp>

extern "C"
{
	#include <libavformat/avformat.h>
}

#include "frame.h"
#include "queue_holder.h"

void deleteFrameFreeFunc(gpointer data)
{
	delete (Frame*)data;
}

void deletePacketFreeFunc(gpointer data)
{
	delete (AVPacket*)data;
}

void deleteStringFreeFunc(gpointer data)
{
	delete (std::string*)data;
}
