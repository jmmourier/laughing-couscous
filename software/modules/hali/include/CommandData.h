#ifndef HALI_COMMAND_DATA_H
#define HALI_COMMAND_DATA_H

#include <string>
#include <vector>
#include <iostream>

struct CommandData{
    void print(){
        std::string printMsg;
        printMsg += "cmd: ";
        printMsg += (command_.empty()) ? "no command" : command_; 
        printMsg += " , args ";
        printMsg += (arguments_.empty()) ? "no args" : arguments_.at(0);
        std::cout << printMsg << std::endl;
    }

    std::string command_;
    std::vector<std::string> arguments_;
};

inline std::ostream& operator<<(std::ostream& os, const CommandData c)
{
    std::string command = (c.command_.empty()) ? "no command" : c.command_; 
    std::string arguments = (c.arguments_.empty()) ? "no args" : c.arguments_.at(0);
    os << "cmd: " << command.c_str() << " , args " << arguments.c_str();
    return os;
}

#endif // HALI_COMMAND_DATA_H