/*
 * queue_user.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef QUEUE_USER_H_
#define QUEUE_USER_H_

template <class QueueType, class ElementType>
class QueueUser {
public:
	// todo
	QueueUser();
	virtual ~QueueUser();
};

// Müssen hier in der Headerdatei definiert werden, sonst meckert der Compiler
template <class QueueType, class ElementType>
QueueUser<QueueType, ElementType>::QueueUser() {
	// TODO Auto-generated constructor stub

}

template <class QueueType, class ElementType>
QueueUser<QueueType, ElementType>::~QueueUser() {
	// TODO Auto-generated destructor stub
}

#endif /* QUEUE_USER_H_ */
