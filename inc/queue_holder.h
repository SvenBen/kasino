/*
 * queue_holder.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef QUEUE_HOLDER_H_
#define QUEUE_HOLDER_H_

#include "queues.h"

void deleteFrameFreeFunc(gpointer data);
void deleteStringFreeFunc(gpointer data);

template <class E>
class QueueHolder
{
private:
	AsyncQueue<E> queue;
	// todo
public:
	QueueHolder(GDestroyNotify free_func);
	virtual ~QueueHolder();
	void push(E e);

protected:
	E timeout_pop(guint64 timeout);
	E try_pop();
};

template <class E>
QueueHolder<E>::QueueHolder(GDestroyNotify free_func) : queue(free_func)
{
	// TODO Auto-generated constructor stub
}

template <class E>
QueueHolder<E>::~QueueHolder()
{
	// TODO Auto-generated destructor stub
}

template <class E>
E QueueHolder<E>::timeout_pop(guint64 timeout = 50000)
{
	return queue.timeout_pop(timeout);
}

template <class E>
E QueueHolder<E>::try_pop()
{
	return queue.try_pop();
}

template <class E>
void QueueHolder<E>::push(E e)
{
	queue.push(e);
}

#endif /* QUEUE_HOLDER_H_ */
