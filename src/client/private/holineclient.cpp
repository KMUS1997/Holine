
#include "holineclient.h"
#include <cmath>
#include <string>
#include "clientversion.h"
#include <vector>
//start asio
#include "asio.hpp"
using asio::ip::tcp;



int main(int argc, char* argv[])
{
	//execute programs with --version follow it, we can print the infomation of the programs
		if (std::string(argv[1]) == "--version") {

			std::cout << "VERSION : " << PROJECT_VERSION << std::endl;
			std::cout << "DESCRIPTION : " << PROJECT_DESCRIPTION << std::endl;
			std::cout << "HOMEPAGE : " << PROJECT_HOMEPAGE_URL << std::endl;
			std::cout << "BINARY : " << PROJECT_BINARY_DIR << std::endl;
			std::cout << "SOURCE : " << PROJECT_SOURCE_DIR << std::endl;
		}

	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		asio::io_context io_context;

		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints =
			resolver.resolve(argv[1], "daytime");

		tcp::socket socket(io_context);
		asio::connect(socket, endpoints);

		for (;;)
		{
			std::vector<char> buf(128);

			asio::error_code error;

			size_t len = socket.read_some(asio::buffer(buf), error);

			if (error == asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw asio::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}



	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}




	return 0;
}

