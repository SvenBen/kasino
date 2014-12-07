/*
 * packet_receiver.h
 *
 *  Created on: Dec 6, 2014
 *      Author: sven
 */

#ifndef PACKET_RECEIVER_H_
#define PACKET_RECEIVER_H_

class MainWindow;

class PacketReceiver
{
private:
	MainWindow* mainWindow;

	// todo
public:
	PacketReceiver(MainWindow* mainWindow);
	virtual ~PacketReceiver();
};

#endif /* PACKET_RECEIVER_H_ */
