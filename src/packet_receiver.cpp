/*
 * packet_receiver.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#include <packet_receiver.h>

#include "windows.h"

PacketReceiver::PacketReceiver(MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
	// TODO Auto-generated constructor stub

}

PacketReceiver::~PacketReceiver()
{
	mainWindow->notifyPackerReceiverDestroyed();
	// TODO Auto-generated destructor stub
}

