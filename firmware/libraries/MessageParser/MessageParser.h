#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include "Arduino.h"
#include "CommandData.h"

class MessageParser{
public:

    MessageParser();

    void setEndChar(char end_char);
    void setSplitChar(char split_char);

    char getEndChar();

    CommandData parse(char* buffer_to_parse);

private:
    CommandsEnum findMessageCommand(char* command);
    char end_char_ = ';';
    char split_char_ = ':';    
};

#endif // MESSAGE_PARSER_H