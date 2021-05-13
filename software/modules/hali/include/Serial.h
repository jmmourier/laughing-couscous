#ifndef HALI_SERIAL_H
#define HALI_SERIAL_H

#include <serialib.h>

class Serial {
   public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     */
    Serial(std::string port, unsigned int baud_rate);

    /**
     * Write a string to the serial device.
     * \param s string to write
     */
    void writeString(std::string s);

    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     */
    std::string readLine();

    /**
     * Blocks until next char is received from the serial device.
     * \return oldest received char
     */
    char readChar();

    void flushReceiver();

   private:
      serialib serial;
};

#endif  // HALI_SERIAL_H