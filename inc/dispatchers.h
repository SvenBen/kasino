/*
 * dispatchers.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef DISPATCHERS_H_
#define DISPATCHERS_H_

#include <glibmm/dispatcher.h>
#include <glibmm/threads.h>

#include "enum_types.h"

class Dispatcher
{
protected:
	Glib::Dispatcher dispatcher;

public:
	Dispatcher(const sigc::slot<void>& slot);
	void notify();
};

template <class T>
class ValueDispatcher : public Dispatcher
{
protected:
	Glib::Threads::Mutex valueMutex;
	T value; // kritisch, wird von mehreren Threads genutzt

public:
	ValueDispatcher(const sigc::slot<void>& slot);
	virtual ~ValueDispatcher();
	void notify(T value);
	T getValue();
};

// Die Member-Funktionen müssen in der Header-Datei definiert werden, da
// der Compiler sonst rummeckert
template <class T>
ValueDispatcher<T>::ValueDispatcher(const sigc::slot<void>& slot) : Dispatcher(slot)
{
}

template <class T>
ValueDispatcher<T>::~ValueDispatcher()
{
}

template <class T>
void ValueDispatcher<T>::notify(T value)
{
	Glib::Threads::Mutex::Lock lock(valueMutex);
	this->value = value;
	dispatcher.emit();
}

template <class T>
T ValueDispatcher<T>::getValue()
{
	Glib::Threads::Mutex::Lock lock(valueMutex);
	return value;
}


#endif /* DISPATCHERS_H_ */
