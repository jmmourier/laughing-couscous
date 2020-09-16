#include <iostream>
#include "src/webInterface/web_ws.hpp"
#include <thread>
#include "webInterface/messages_handler.h"

int main() {

    messages_handler mh;

    //run web interface
    std::thread websockServer(start_server, mh);

    websockServer.join();
    return 0;
}
