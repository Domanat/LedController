#include "Client.hpp"

Client::Client(boost::asio::io_context& context, std::string ipAddr, int portNum):
		ioContext(context),
		socket(ioContext),
		ip(ipAddr),
		port(portNum)
	{

	}

void Client::Start()
	{
		socket.async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port),
			[this](const boost::system::error_code& ec)
			{
				if (ec.failed())
				{
					std::cout << "Error connecting to server: " << ec.message() << std::endl;
					return;
				}

				std::cout << "Connected successfully" << std::endl;
				Communicate();
			});
	}

	void Client::Communicate()
	{
		WriteRequest();
		ReadResponse();

	}

	void Client::WriteRequest()
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, request);

		request += '\n';

		boost::asio::async_write(socket, boost::asio::buffer(request),
			[this](const boost::system::error_code& ec, std::size_t bytes)
			{
				if (ec.failed())
				{
					std::cout << "Error writing request: " << ec.message() << std::endl;
					return;
				}
			});
	}

	void Client::ReadResponse()
	{
		boost::asio::async_read_until(socket, buffer, '\n',
			[this](const boost::system::error_code& ec, std::size_t bytes)
			{
				if (ec.failed())
				{
					std::cout << "Error reading response: " << ec.message() << std::endl;
					return;
				}

				std::istream input(&buffer);
				std::getline(input, response);

				std::cout << response << std::endl;

				Communicate();
			});
	}