#include "Serial.h"

#include <serialib.h>
#include <iostream>

Serial::Serial(std::string port, unsigned int baud_rate) {
     char errorOpening = serial.openDevice(port.c_str(), baud_rate);

    if (errorOpening!=1) throw "[hali] Port can not be open";
}

void Serial::writeString(std::string string_input) {
    serial.writeString(string_input.c_str());
}

std::string Serial::readLine() {
    char c;
    std::string result;
    for (;;) {
        serial.readChar(&c);
        switch (c) {
            case '\r':
                break;
            case '\n':
                return result;
            default:
                result += c;
        }
    }
}

char Serial::readChar() {
    char c;
    try {
        serial.readChar(&c);
    } catch (const std::exception &e) {
        // std::cout << e.what() << std::endl;
        return 0;
    }
    return c;
}
