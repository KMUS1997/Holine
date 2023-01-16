// Holine.cpp : Defines the entry point for the application.
//

#include "holineserver.h"
#include <cmath>
#include <string>

#include "serverversion.h"
#include <functional>
#include <ctime>
#include <memory>
//start asio
#include "asio.hpp"

using asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}


class tcp_connection
	: public std::enable_shared_from_this<tcp_connection>
{
public:
	typedef std::shared_ptr<tcp_connection> pointer;

	static pointer create(asio::io_context& io_context)
	{
		return pointer(new tcp_connection(io_context));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		asio::async_write(socket_, asio::buffer(message_),
			std::bind(&tcp_connection::handle_write, shared_from_this(),
				std::placeholders::_1,
				std::placeholders::_2));
	}

private:
	tcp_connection(asio::io_context& io_context)
		: socket_(io_context)
	{
	}

	void handle_write(const asio::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}

	tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(asio::io_context& io_context)
		: io_context_(io_context),
		acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection = tcp_connection::create(io_context_);

		acceptor_.async_accept(new_connection->socket(),
			std::bind(&tcp_server::handle_accept, this, new_connection,
				std::placeholders::_1));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const asio::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
		}

		start_accept();
	}

	asio::io_context& io_context_;
	tcp::acceptor acceptor_;
};



int main(int argc, char* argv[])
{
	// execute programs with --version follow it ,we can print the infomation of the programs
	if (argc > 1) {
		if (std::string(argv[1]) == "--version") {

			std::cout << "Version : " << PROJECT_VERSION_MAJOR << "."
				<< PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << '.' << PROJECT_VERSION_TWEAK << std::endl;

			std::cout << "DESCRIPTION : " << PROJECT_DESCRIPTION << std::endl;
			std::cout << "HOMEPAGE : " << PROJECT_HOMEPAGE_URL << std::endl;
			std::cout << "BINARY : " << PROJECT_BINARY_DIR << std::endl;
			std::cout << "SOURCE : " << PROJECT_SOURCE_DIR << std::endl;
		}
	}
	try
	{
		asio::io_context io_context;
		tcp_server server(io_context);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

