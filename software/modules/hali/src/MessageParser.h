#include <string>
#include <vector>
#include <iostream>

struct CommandData{
    void print(){
        std::string printMsg;
        printMsg += "cmd: ";
        printMsg += (command.empty()) ? "no command" : command; 
        printMsg += " , args ";
        printMsg += (arguments.empty()) ? "no args" : arguments.at(0);
        std::cout << printMsg << std::endl;
    }

    std::string command;
    std::vector<std::string> arguments;
};

class MessageParser
{
public:
    MessageParser();

    void addCharToBuffer(char charToAdd);

    CommandData analyseBuffer();

    void clearBuffer();

    void setSplitChar(char splitChar);

    void setEndChar(char endChar);

    void printBuffer() {std::cout << "buffer : " << buffer_ << std::endl;}

    std::string createMessage(CommandData);

private:
    bool isCharAllowed(char testedChar);
    std::string buffer_;
    const int buffer_allocation_size_;
    char splitChar_ = ':';
    char endChar_ = ';';
};