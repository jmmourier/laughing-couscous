#include <iostream>
#include "SimpleSerial.h"


int main(int argc, char* argv[])
{
    try {

        SimpleSerial serial("/dev/ttyACM0",9600);

        serial.writeString("Hello world\n");

        std::cout<<serial.readLine()<<std::endl;

    } catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }
}
