#include "CouscousManager.h"

#include "Hali.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 50;

CouscousManager::CouscousManager(std::shared_ptr<Hali> hali) : hali_(std::move(hali)) {
    auto time_helper = std::make_shared<RealTime>();

    double start_pos_x_m = 1;
    double start_pos_y_m = 1;
    double start_orientation_rad = 0;

    posi_ =
        std::make_shared<Posi>(time_helper, start_pos_x_m, start_pos_y_m, start_orientation_rad);

    web_server_ = std::make_shared<WebServer>(
        [&](double pos_x_m, double pos_y_m, double orientation_rad) {
            onClientRequestSetPosition(pos_x_m, pos_y_m, orientation_rad);
        },
        [&](int motor1, int motor2) { onClientRequestSetSpeed(motor1, motor2); });

    web_server_thread_ = std::thread([this] { web_server_->start(); });
}

void CouscousManager::onPosiPositionUpdate(double pos_x_m, double pos_y_m, double orientation_rad) {
    web_server_->updatePosition(pos_x_m, pos_y_m, orientation_rad);
}

void CouscousManager::onClientRequestSetPosition(
    double pos_x_m,
    double pos_y_m,
    double orientation_rad) {
    posi_->setPosition(pos_x_m, pos_y_m, orientation_rad);
};

void CouscousManager::onClientRequestSetSpeed(int motor1, int motor2) {
    hali_->setMd25Speed(motor1, motor2);
};

void CouscousManager::start() {
    while (true) {
        int encoder1 = hali_->getEncoder(MotorIdEnum::motor1);
        int encoder2 = hali_->getEncoder(MotorIdEnum::motor2);

        posi_->updatePosition(encoder1, encoder2);

        // Send new position to gui
        double abs_pos_x_m = 0;
        double abs_pos_y_m = 0;
        double abs_orientation_rad = 0;

        posi_->getPosition(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);
        onPosiPositionUpdate(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);
        // ---------------------------

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
}