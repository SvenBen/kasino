/*
 * KasinoException.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#include "kasino_exception.h"
#include "kasino_strings.h"

KasinoException::KasinoException()
{
}

KasinoException::KasinoException(const std::string& m)
{
	msg = std::string(m);
}

const std::string& KasinoException::what() const
{
	return msg;
}

NotEnoughSpaceException::NotEnoughSpaceException() : KasinoException(STR_NOT_ENOUGH_SPACE)
{
}

FileOpenException::FileOpenException(const std::string& filename)  : KasinoException(STR_COULD_NOT_OPEN + filename)
{
}
