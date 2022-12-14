#include "Client.hpp"

int main()
{
	try
	{
		boost::asio::io_context ioContext{ 2 };
			
		Client client(ioContext, "127.0.0.1", 9988);
		client.Start();

		ioContext.run();
		
	}
	catch (...)
	{
		std::cout << "Error has happened" << std::endl;
		return -1;
	}

	return 0;
}