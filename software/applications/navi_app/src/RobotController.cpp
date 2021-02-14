
#include "RobotController.h"
#include <Navi.h>
#include <iostream>
#include "Hali.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 50;

RobotController::RobotController(std::shared_ptr<Hali> hali) : hali_(std::move(hali)) {
    auto time_helper = std::make_shared<RealTime>();
    double start_pos_x_m = 1;
    double start_pos_y_m = 1;
    double start_orientation_rad = 0;
    posi_ = std::make_shared<Posi>(time_helper, start_pos_x_m, start_pos_y_m, start_orientation_rad);
    nav_ = std::make_shared<Navi>([&](int motor1, int motor2) { onClientRequestSetSpeed(motor1, motor2); });
}

void RobotController::onPosiPositionUpdate(double pos_x_m, double pos_y_m, double orientation_rad) {
}

void RobotController::onClientRequestSetPosition(double pos_x_m, double pos_y_m, double orientation_rad) {
    nav_->setTargetPosition(pos_x_m, pos_y_m, orientation_rad);

}

void RobotController::onClientRequestSetSpeed(int motor1, int motor2) {
    hali_->setMd25Speed(motor1, motor2);
}


void RobotController::start() {
  // onClientRequestSetSpeed(0.1, 0.1);

  posi_->setPosition(1,1,0);
    while (true) {
        int encoder1 = hali_->getEncoder(MotorIdEnum::motor1);
        int encoder2 = hali_->getEncoder(MotorIdEnum::motor2);
        posi_->updatePosition(encoder1, encoder2);

        double abs_pos_x_m = 0;
        double abs_pos_y_m = 0;
        double abs_orientation_rad = 0;
        posi_->getPosition(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);

        //std::cout<<"encoder1:"<<encoder1<<" encoder2:"<<encoder2<<" posX:"<<abs_pos_x_m<<" posY:"<<abs_pos_y_m<<" angle:"<<abs_orientation_rad<<std::endl;
        //std::cout<<"[RobotController]nav state: "<<nav_->getActualState()<<std::endl;
        nav_->setCurrentPosition(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
}