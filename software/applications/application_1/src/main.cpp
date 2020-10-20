#include <iostream>
#include <thread>

#include "HalReal.h"
#include "HalSimu.h"
#include "Hali.h"
#include "src/webInterface/messages_handler.h"
#include "src/webInterface/web_ws.hpp"

int main(int argc, char *argv[]) {
    try {
        Hali *hali;
        if (argc > 1) {
            if (std::string(argv[1]) == "-r") {
                auto realhali = new HalReal();
                hali = realhali;
            } else {
                auto realhali = new HalSimu();
                hali = realhali;
            }
        } else {
            auto realhali = new HalSimu();
            hali = realhali;
        }

        // init gui
        messages_handler mh(hali);
        std::thread websockServer(start_server, mh);

        websockServer.join();
        std::cout << "done" << std::endl;
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
