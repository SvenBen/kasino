
#include <cstdlib>
#include <iostream>
#include <glibmm/exception.h>

#include "application.h"
#include "kasino_exception.h"

int main(int argc, char* argv[])
{
	try
	{
		Application app(argc, argv);
		app.run();
	}
	catch (Glib::Exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (KasinoException& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
