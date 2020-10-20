#ifndef HALI_MESSAGE_PARSER_H
#define HALI_MESSAGE_PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "CommandData.h"

class MessageParser {
   public:
    MessageParser();

    void addCharToBuffer(char charToAdd);

    CommandData analyseBuffer();

    void clearBuffer();

    void setSplitChar(char splitChar);

    void setEndChar(char endChar);

    void printBuffer() {
        std::cout << "buffer : " << buffer_ << std::endl;
    }

    std::string createMessage(CommandData);

   private:
    bool isCharAllowed(char testedChar);

    std::string buffer_;
    const int buffer_allocation_size_;
    char splitChar_ = ':';
    char endChar_ = ';';
};

#endif  // HALI_MESSAGE_PARSER_H