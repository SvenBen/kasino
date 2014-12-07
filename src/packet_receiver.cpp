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
	mainWindow->log("Packet Receiver erstellt");
}

PacketReceiver::~PacketReceiver()
{
	mainWindow->notifyPacketReceiverDestroyed();
	mainWindow->log("Packet Receiver zerstört");
	// TODO Auto-generated destructor stub
}

