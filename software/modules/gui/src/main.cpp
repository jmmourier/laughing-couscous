#include <iostream>
#include "src/webInterface/web_ws.hpp"
#include <thread>
#include "webInterface/messages_handler.h"
#include "registry.h"
int main() {

    //run registry
    registry r;

    messages_handler mh(r);

    //run web interface
    std::thread websockServer(start_server, mh);

    websockServer.join();
    return 0;
}
