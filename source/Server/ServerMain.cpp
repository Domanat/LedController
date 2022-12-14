#include "Server.hpp"

int main()
{
	try
	{
		boost::asio::io_context ioContext{ 2 };
		Server server(ioContext, 9988);

		server.Start();

		ioContext.run();

		std::cout << "Here" << std::endl;
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	return 0;
}