#include <Navi.h>
#include <Posi.h>
#include <RealTime.h>
#include <RobotController.h>
#include <iostream>
#include <memory>
#include <thread>
#include <iostream>
#include "HalSimu.h"
#include "Hali.h"

#include <functional>


void testfunc( std::shared_ptr<RobotController> rc){
    double targetX=2.0;
    double targetY=2.0;
    double angle=0.0;
    for(;;){
        while (std::cin.get() != '\n');

        std::cout<<"set target"<<std::endl;
        std::cout<<"target is:"<<targetX<<" "<<targetY<<std::endl;
        rc->onClientRequestSetPosition(1.0,1.0,0.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char *argv[]) {
    //ok
    //auto robotController = std::make_shared<RobotController>(std::make_shared<HalSimu>());
    //robotController->start();

    // testfunc();

    //return 0;
    //testing
    auto robotController = std::make_shared<RobotController>(std::make_shared<HalSimu>());
    std::thread tf(testfunc, robotController);
    robotController->start();

    return 0;
}
