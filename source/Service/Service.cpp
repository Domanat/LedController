#include "Service.hpp"

Service::Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock, LED &l) : socket(sock),
                                                                               led(l)
{
}

void Service::StartHandling()
{
    boost::asio::async_read_until(*socket, buffer, '\n',
                                  [this](const boost::system::error_code &ec, std::size_t bytes)
                                  {
                                      if (ec.failed())
                                      {
                                          std::cout << "Error reading from socket" << std::endl;
                                          OnFinish();
                                          return;
                                      }
                                      OnRead();
                                  });
}

void Service::OnRead()
{
    std::istream input(&buffer);
    std::getline(input, request);

    ParseRequest();
    WriteResponse();
}

void Service::ParseRequest()
{
    // Choose what is the command
    response = "Empty";

    if (request.substr(0, rateCommandSize) == "set-led-rate" && request.size() > rateCommandSize)
    {
        std::string value = request.substr(rateCommandSize + 1);

        std::regex expr("[0-9]+\.\.[0-9]+");

        // Expression is okay
        if (std::regex_match(value, expr))
        {

            // Position of first dot
            std::size_t dotPos = value.find('.');
            if (dotPos != value.npos)
            {
                // Cut out first dot
                value.erase(dotPos, 1);

                double newRate = std::stod(value);
                led.SetRate(newRate);

                response = "OK";
            }
        }
        else
        {
            response = "FAILED";
        }
    }
    else if (request.substr(0, rateCommandSize) == "get-led-rate")
    {
        double rate = led.GetRate();

        response = "OK | " + std::to_string(rate);
    }
    else if (request.substr(0, colorCommandSize) == "set-led-color" && request.size() > colorCommandSize)
    {
        std::string value = request.substr(colorCommandSize + 1);

        std::regex expr("(red|green|blue)");

        // Expression is okay
        if (std::regex_match(value, expr))
        {
            Color newColor;

            if (value == "red")
                newColor = Color::red;
            else if (value == "green")
                newColor = Color::green;
            else
                newColor = Color::blue;

            led.SetColor(newColor);

            response = "OK";
        }
        else
        {
            response = "FAILED";
        }
    }
    else if (request.substr(0, colorCommandSize) == "get-led-color")
    {
        Color color = led.GetColor();

        response = "OK | ";

        if (color == Color::red)
            response += "red";
        else if (color == Color::green)
            response += "green";
        else
            response += "blue";
    }
    else if (request.substr(0, stateCommandSize) == "set-led-state" && request.size() > stateCommandSize)
    {
        std::string value = request.substr(stateCommandSize + 1);

        std::regex expr("(on|off)");

        // Expression is okay
        if (std::regex_match(value, expr))
        {
            bool state = false;

            if (value == "on")
                state = true;
            else
                state = false;
            // else state = false

            led.SetState(state);

            response = "OK";
        }
        else
        {
            response = "FAILED";
        }
    }
    else if (request.substr(0, stateCommandSize) == "get-led-state")
    {
        bool state = led.GetState();

        response = "OK | ";
        if (state)
            response += "ON";
        else
            response += "OFF";
    }
    else
    {
        response = "FAILED";
    }

    response += "\n";
}

void Service::WriteResponse()
{
    // Write response
    boost::asio::async_write(*socket, boost::asio::buffer(response),
                             [this](const boost::system::error_code &ec, std::size_t bytes)
                             {
                                 if (ec.failed())
                                 {
                                     std::cout << "Error writing to socket" << std::endl;
                                     OnFinish();
                                     return;
                                 }

                                 StartHandling();
                             });
}

void Service::OnFinish()
{
    delete this;
}