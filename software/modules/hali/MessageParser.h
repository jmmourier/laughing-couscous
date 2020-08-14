#include <string>
#include <vector>
#include <iostream>

struct CommandData{
    void print(){
        std::cout<< "cmd: ";
        if(!command.empty())
        {
            std::cout << command;
        } else
        {
            std::cout << "no command";
        }
        std::cout <<  " , args ";
        if(!arguments.empty())
        {
            std::cout << arguments.at(0);
        }
        else
        {
            std::cout << "no args";
        }
        std::cout << std::endl;
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

private:
    bool isCharAllowed(char testedChar);
    std::string buffer_;
    const int buffer_allocation_size_;
    char splitChar_ = ':';
    char endChar_ = ';';
};