#include <boost/asio.hpp>
#include <iostream>
#include "Serial.h"

Serial::Serial(std::string port, unsigned int baud_rate)
: io(), serial(io,port)
{
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

void Serial::writeString(std::string s)
{
    std::cout << "writing : " << s << std::endl;
    boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
}

std::string Serial::readLine()
{
    char c;
    std::string result;
    for(;;)
    {
        boost::asio::read(serial,boost::asio::buffer(&c,1));
        switch(c)
        {
            case '\r':
                break;
            case '\n':
                return result;
            default:
                result+=c;
        }
    }
}

char Serial::readChar()
{
    char c;
    try
    {
        boost::asio::read(serial,boost::asio::buffer(&c,1));
    }
    catch(const std::exception& e)
    {
        //std::cout << e.what() << std::endl;
        return 0;
    }
    return c;
}

