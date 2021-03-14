
#include "CouscousManager.h"

#include "Posi.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 50;

CouscousManager::CouscousManager(
    const std::shared_ptr<IHali> &hali,
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

void CouscousManager::onWebServerPositionRequest(
    const double &pos_x_m,
    const double &pos_y_m,
    const double &orientation_rad) {
    posi_->setPosition(pos_x_m, pos_y_m, orientation_rad);
}

void CouscousManager::onWebServerSpeedRequest(const int &speed_motor1, const int &speed_motor2) {
    hali_->setMd25Speed(speed_motor1, speed_motor2);
};

void CouscousManager::onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) {
    // Will be sent to navi
}

void CouscousManager::onSpeedChanged(const int &motor1, const int &motor2) {
    // Will be sent to navi
}

void CouscousManager::start() {
    while (true) {
        int encoder1 = hali_->getEncoder(MotorIdEnum::motor1);
        int encoder2 = hali_->getEncoder(MotorIdEnum::motor2);

        posi_->updatePosition(encoder1, encoder2);

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
}