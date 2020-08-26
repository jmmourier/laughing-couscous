#include <iostream>

#include "MessageParser.h"

MessageParser::MessageParser():buffer_allocation_size_(50){}

void MessageParser::addCharToBuffer(char char_to_add){
    if(isCharAllowed(char_to_add)){
        if(buffer_.size() >= buffer_allocation_size_)
        {
            std::cout << "[MessageParser] buffer overflow" << std::endl;    
            buffer_.erase(buffer_.begin());
        }
        buffer_.push_back(char_to_add);
    }
    else
    {
        std::cout << "[MessageParser] forbidden char received" << std::endl;
    }
}

CommandData MessageParser::analyseBuffer(){
    CommandData returned_command_data;

    std::size_t position_of_end_char = buffer_.find_first_of(endChar_);
    
    if(position_of_end_char == std::string::npos){
        std::cout << "[MessageParser] no end char found during analyse" << std::endl;
    }
    else
    {   
        std::cout << "[MessageParser] end char found during analyse" << std::endl;    
        std::size_t position_of_first_split_char = buffer_.find_first_of(splitChar_);

        if(position_of_end_char == 0){
            std::cout << "[MessageParser] message is empty" << std::endl;
            buffer_.erase(0,1);
        }
        else if(position_of_first_split_char == 0) {
            std::cout << "[MessageParser] no command in message" << std::endl;
            buffer_.erase(0,position_of_end_char+1);
        }
        else if(position_of_first_split_char == std::string::npos || 
            position_of_first_split_char > position_of_end_char) {
            std::cout << "[MessageParser] no split char found during analyse" << std::endl;
            returned_command_data.command = buffer_.substr(0,position_of_end_char);
            buffer_.erase(0,position_of_end_char+1);
        }
        else {
            returned_command_data.command = buffer_.substr(0,position_of_first_split_char);

            if(position_of_end_char > position_of_first_split_char + 1){
                returned_command_data.arguments.emplace_back(buffer_.substr(position_of_first_split_char + 1 , position_of_end_char - position_of_first_split_char - 1));
            }

            buffer_.erase(0,position_of_end_char + 1);
        }
        // TODO :
        // handle when more than 1 arg
        // find all the split char and add all substring to the vector
        // of returned_command_data.        
    }
    return returned_command_data;
}

void MessageParser::clearBuffer(){
    buffer_.clear();
}

void MessageParser::setSplitChar(char split_char){
    splitChar_ = split_char;
}

void MessageParser::setEndChar(char end_char){
    endChar_ = end_char;
}

bool MessageParser::isCharAllowed(char testedChar){
    //we only keep ascii value, point, endChar and splitChar
    std::string allowedLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    std::string allowedNumbers = "0123456789";
    std::string allowedPonctuation = ".";

    return (allowedLetters.find(testedChar,0) != std::string::npos ||
            allowedNumbers.find(testedChar,0) != std::string::npos ||
            allowedPonctuation.find(testedChar,0) != std::string::npos ||
            testedChar == endChar_ ||
            testedChar == splitChar_);
}

std::string MessageParser::createMessage(CommandData dataToSend){
    std::string messageToSend;
    messageToSend += dataToSend.command;
    messageToSend += splitChar_;
    messageToSend += (!dataToSend.arguments.empty()) ? dataToSend.arguments.at(0) : "";
    messageToSend += endChar_;
    return messageToSend;
}