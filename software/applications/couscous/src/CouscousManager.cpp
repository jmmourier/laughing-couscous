
#include "CouscousManager.h"

#include "Posi.h"
#include "RealTime.h"

CouscousManager::CouscousManager(
    const std::shared_ptr<IHali> &hali,
    const std::shared_ptr<Posi> &posi,
    const std::shared_ptr<WebServer> &web_server)
    : hali_(hali),
      posi_(posi),
      web_server_(web_server) {
    web_server_thread_ = std::thread([&] { web_server_->start(); });
}

void CouscousManager::onPositionChanged(const PositionOrientation &position_orientation) {
    web_server_->setPosition(position_orientation);
}

void CouscousManager::onWebServerPositionRequest(const PositionOrientation &position_orientation) {
    posi_->setPosition(position_orientation);
}

void CouscousManager::onWebServerSpeedRequest(const int &speed_motor1, const int &speed_motor2) {
    hali_->setMd25Speed(speed_motor1, speed_motor2);
}

void CouscousManager::onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) {
    // Will be sent to navi
}

void CouscousManager::onEncodersChanged(const int &encoders_motor1, const int &encoders_motor2) {
    // Will be sent to navi
    posi_->updatePosition(encoders_motor1, encoders_motor2);
}

void CouscousManager::start() {
    hali_->updater();
    web_server_thread_.join();
}