#include <iostream>
#include "src/webInterface/web_ws.hpp"
#include <thread>
#include "webInterface/messages_handler.h"
int main() {

    std::thread websockServer(start_server);
    websockServer.join();
    return 0;
}
