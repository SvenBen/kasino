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
AsyncQueue<E>::AsyncQueue(GDestroyNotify free_func = NULL)
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

void deletePacketFreeFunc(gpointer data);
void deleteStringFreeFunc(gpointer data);


template <class E>
class QueueHolder;

template <class E>
class QueueUser
{
private:
	QueueHolder<E>* queueHolder;

public:
	// todo
	QueueUser(QueueHolder<E>* holder);
	virtual ~QueueUser();

	void push(E e);
};

// Müssen hier in der Headerdatei definiert werden, sonst meckert der Compiler
template <class E>
QueueUser<E>::QueueUser(QueueHolder<E>* holder)
{
	queueHolder = holder;
	// TODO Auto-generated constructor stub

}

template <class E>
QueueUser<E>::~QueueUser()
{
	// TODO Auto-generated destructor stub
}

template <class E>
void QueueUser<E>::push(E e)
{
	queueHolder->push(e);
}


template <class E>
class QueueHolder
{
private:
	AsyncQueue<E> queue;
	// todo
public:
	QueueHolder(GDestroyNotify free_func = NULL);
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

#endif /* QUEUES_H_ */
