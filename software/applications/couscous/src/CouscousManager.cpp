
#include "CouscousManager.h"

#include "Hali.h"
#include "Posi.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 50;

CouscousManager::CouscousManager(
    const std::shared_ptr<Hali> &hali,
    const std::shared_ptr<Posi> &posi,
    const std::shared_ptr<WebServer> &web_server)
    : hali_(hali),
      posi_(posi),
      web_server_(web_server) {
    web_server_thread_ = std::thread([&] { web_server_->start(); });
}

void CouscousManager::onPositionChanged(
    const double &pos_x_m,
    const double &pos_y_m,
    const double &orientation_rad) {
    web_server_->setPosition(pos_x_m, pos_y_m, orientation_rad);
}

void CouscousManager::onPositionRequested(
    const double &pos_x_m,
    const double &pos_y_m,
    const double &orientation_rad) {
    posi_->setPosition(pos_x_m, pos_y_m, orientation_rad);
};

void CouscousManager::onSpeedRequested(const int &speed_motor1, const int &speed_motor2) {
    hali_->setMd25Speed(speed_motor1, speed_motor2);
};

void CouscousManager::start() {
    while (true) {
        int encoder1 = hali_->getEncoder(MotorIdEnum::motor1);
        int encoder2 = hali_->getEncoder(MotorIdEnum::motor2);

        posi_->updatePosition(encoder1, encoder2);

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
}