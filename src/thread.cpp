/*
 * thread.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sven
 */

#include <assert.h>

#include "thread.h"

Thread::Thread()
{
	quit = false;
	thread = NULL;
}

Thread::~Thread()
{
	// TODO Auto-generated destructor stub
}
