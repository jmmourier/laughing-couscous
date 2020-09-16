#include <iostream>
#include "src/webInterface/web_ws.hpp"
#include <thread>
#include "src/webInterface/messages_handler.h"
#include "Hali.h"
#include "HalSimu.h"


void testfunction(int i){
    std::cout << "callback "<<i<<std::endl;
}


double binary_op(double left, double right, double (*f)(double, double)) {
    std::cout<<"callback"<<std::endl;
}

int main() {

    //init hali
    Hali* hali;
    auto realhali = new HalSimu();
    hali = realhali;

    //init gui
    messages_handler mh;
    //std::thread websockServer(start_server, mh);

   mh.cbtest(testfunction);

   // std::cout << "md25 voltage  : " << hali->getBatteryVoltage() << std::endl;

    //websockServer.join();
    std::cout<<"done"<<std::endl;
    return 0;
}
