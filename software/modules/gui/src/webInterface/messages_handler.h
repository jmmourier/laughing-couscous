#ifndef SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
#define SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H

#include <string>
#include "../registry.h"

class messages_handler {

public:
    messages_handler(registry r);
    void handle_message(const std::string msg_str, std::string &ret);

};


#endif //SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
