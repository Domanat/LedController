#include <boost/asio.hpp>
#include <iostream>
#include <string>

class Client
{
public:
	Client(boost::asio::io_context& context, std::string ipAddr, int portNum);

	void Start();

	void Communicate();

	void WriteRequest();

	void ReadResponse();

private:
	boost::asio::io_context& ioContext;
	boost::asio::ip::tcp::socket socket;

	boost::asio::streambuf buffer;

	std::string request;
	std::string response;

	std::string ip;
	int port;
};