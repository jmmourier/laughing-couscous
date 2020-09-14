#include <iostream>
#include "src/webInterface/web_ws.hpp"
#include <thread>
#include "src/webInterface/messages_handler.h"
#include "Hali.h"
#include "HalSimu.h"
int main() {
    Hali* hali;
    auto realhali = new HalSimu();
    hali = realhali;
    std::cout << "md25 voltage  : " << hali->getBatteryVoltage() << std::endl;
    return 0;

    messages_handler mh;

    //run web interface
    std::thread websockServer(start_server, mh);

    websockServer.join();
    return 0;
}
