/*
 * frame.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sven
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>

class Frame
{
	// todo
public:
	Frame();
	virtual ~Frame();
};

typedef boost::shared_ptr<Frame> SharedFramePtr;

#endif /* FRAME_H_ */
