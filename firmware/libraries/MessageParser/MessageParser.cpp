#include <string.h>
#include "MessageParser.h"

MessageParser::MessageParser(){

}

void MessageParser::setEndChar(char end_char){
    end_char_ = end_char;
}
void MessageParser::setSplitChar(char split_char){
    split_char_ = split_char;
}

char MessageParser::getEndChar(){
    return end_char_;
}

CommandData MessageParser::parse(char* buffer_to_parse){
    char* message = strtok(buffer_to_parse, end_char_);

    if(message != 0){
        char* separator = strchr(message, split_char_);
        if (separator != 0)
        {
            // Actually split the string in 2: replace ':' with 0
            *separator = 0;
            CommandsEnum command = findMessageCommand(message);
            ++separator;
            int argument = atoi(separator);
            return CommandData(command,argument);
        }
        else
        {
            return CommandData(-1,0);
        }
    }
}    

CommandsEnum MessageParser::findMessageCommand(char* command){
    CommandsMessage list_of_messages;
    for(int i=0; i<CommandsEnumMax; i++)
    {            
        if(strcmp(command,list_of_messages.Messages_[i]) == 0 
        && strcmp(command,"")!=0){
            return i;
        }
    }
    return -1;
}