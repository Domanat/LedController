#include "Server.hpp"

    Server::Server(boost::asio::io_context& context, int portNum) :
		ioContext(context),
		port(portNum)
	{
		work.reset(new boost::asio::io_context::work(ioContext));

        acceptor.reset(new boost::asio::ip::tcp::acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port)));

		acceptor->listen();

		for (int i = 0; i < 2; i++)
		{
			std::unique_ptr<std::thread> th(new std::thread([this]() {
				ioContext.run();
				}));

			threadPool.push_back(std::move(th));
		}
	}

	void Server::Start()
	{

		std::shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(ioContext));
		
		acceptor->async_accept(*socket, [this, socket](const boost::system::error_code& ec)
			{
				if (ec.failed())
				{
                    std::cout << "Error accepting client: " << ec.message() << std::endl;
					return;
				}
				else
				{
                    std::cout << "Client accepted" << std::endl;
					(new Service(socket, led))->StartHandling();
				}

				Start();
			});
	}

	void Server::Stop()
	{
		acceptor->close();
		ioContext.stop();

		for (auto& th : threadPool)
		{
			th->join();
		}
	}