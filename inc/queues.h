/*
 * queues.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef QUEUES_H_
#define QUEUES_H_

#include <glib.h>
#include <assert.h>

template <class E>
class AsyncQueue
{
private:
	GAsyncQueue *queue;

public:
	AsyncQueue(GDestroyNotify free_func);
	virtual ~AsyncQueue();
	void push(E element);
	E timeout_pop(guint64 timeout);
	E try_pop();
};


template <class E>
AsyncQueue<E>::AsyncQueue(GDestroyNotify free_func)
{
	if (free_func == NULL)
	{
		queue = g_async_queue_new();
	}
	else
	{
		queue = g_async_queue_new_full(free_func);
	}
}

template <class E>
AsyncQueue<E>::~AsyncQueue()
{
	g_async_queue_unref(queue);
	queue = NULL;
}

template <class E>
void AsyncQueue<E>::push(E element)
{
	g_async_queue_push(queue, element);
}

template <class E>
E AsyncQueue<E>::timeout_pop(guint64 timeout = 50000)
{
	E e = (E)g_async_queue_timeout_pop(queue, timeout);
	return e;
}

template <class E>
E AsyncQueue<E>::try_pop()
{
	E e = NULL;
	e = (E)g_async_queue_try_pop(queue);

	return e;
}

#endif /* QUEUES_H_ */
