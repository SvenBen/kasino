/*
 * kasino_exception.h
 *
 *  Created on: Dec 4, 2014
 *      Author: sven
 */

#ifndef KASINO_EXCEPTION_H_
#define KASINO_EXCEPTION_H_

#include <string>

class KasinoException
{
private:
	std::string msg;

public:
	KasinoException();
	KasinoException(const std::string& m);

	const std::string& what() const;
};

class NotEnoughSpaceException : public KasinoException
{
public:
	NotEnoughSpaceException();
};

class FileOpenException : public KasinoException
{
public:
	FileOpenException(const std::string& filename);
};

#endif /* KASINO_EXCEPTION_H_ */
