/*
 * queue_user.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef QUEUE_USER_H_
#define QUEUE_USER_H_

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

#endif /* QUEUE_USER_H_ */
