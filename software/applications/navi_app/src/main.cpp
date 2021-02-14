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


void keyEntry( std::shared_ptr<RobotController> rc){
    double targetX=1.2;
    double targetY=1.2;
    double angle=0.0;
    for(;;){
        while (std::cin.get() != '\n');
        std::cout<<"set taget target:"<<targetX<<" "<<targetY<<std::endl;
        rc->onClientRequestSetPosition(targetX,targetY,0.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char *argv[]) {
    auto robotController = std::make_shared<RobotController>(std::make_shared<HalSimu>());
    std::thread tf(keyEntry, robotController);
    robotController->start();

    return 0;
}
