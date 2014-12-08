/*
 * thread.h
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <glibmm/threads.h>

class Thread
{
protected:
	Glib::Threads::Thread* thread;
	bool quit;

public:
	Thread();
	virtual ~Thread();

public:
	virtual void threadFunc() = 0;
};

#endif /* THREAD_H_ */
