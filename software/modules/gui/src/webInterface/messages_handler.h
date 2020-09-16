#ifndef SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
#define SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H

#include <string>

class messages_handler {

public:
//    void cbtest(void  (*f)(void);
    void cbtest( void (*f)(int));
    void handle_message(const std::string msg_str, std::string &ret);

private:

};

#endif //SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
