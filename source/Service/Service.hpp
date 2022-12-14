#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <regex>

#include "../LED/LED.hpp"

class Service
{
public:
	Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock, LED& l);

	void StartHandling();

private:

	void OnRead();

	void ParseRequest();

	void WriteResponse();

	void OnFinish();

	std::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::string response;
	std::string request;
	boost::asio::streambuf buffer;

	LED& led;

	unsigned int rateCommandSize = 12;
	unsigned int colorCommandSize = 13;
	unsigned int stateCommandSize = 13;
};