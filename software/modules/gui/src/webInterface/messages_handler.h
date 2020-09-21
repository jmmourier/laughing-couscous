#ifndef SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
#define SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H

#include <string>
#include "Hali.h"
#include "HalSimu.h"
class messages_handler {

public:
    messages_handler(Hali *hali);
    void handle_message(const std::string msg_str, std::string &ret);
private:
    Hali* _hali;
};

#endif //SIMPLE_WEBSOCKET_SERVER_MESSAGES_HANDLER_H
