
#include "../Service/Service.hpp"

class Server
{
public:
	Server(boost::asio::io_context& context, int portNum);

	void Start();

	void Stop();
private:

	boost::asio::io_context& ioContext;
	std::unique_ptr<boost::asio::io_context::work> work;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
	std::vector<std::unique_ptr<std::thread>> threadPool;

	std::unique_ptr<Service> service;
	int port;
	std::string ip = "127.0.0.1";

	LED led;
};



