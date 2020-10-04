#include "CouscousManager.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 500;

CouscousManager::CouscousManager() {
  auto time_helper = std::make_shared<RealTime>();

  double start_pos_x_m = 0;
  double start_pos_y_m = 0;
  double start_orientation_rad = 0;

  posi_ = std::make_shared<Posi>(time_helper, start_pos_x_m, start_pos_y_m,
                                 start_orientation_rad);

  web_server_ = std::make_shared<WebServer>(
      [&](double pos_x_m, double pos_y_m, double orientation_rad) {
        onClientRequestSetPosition(pos_x_m, pos_y_m, orientation_rad);
      });

  web_server_thread_ = std::thread([this] { web_server_->start(); });
}

void CouscousManager::onPosiPositionUpdate(double pos_x_m, double pos_y_m,
                                           double orientation_rad) {
  web_server_->updatePosition(pos_x_m, pos_y_m, orientation_rad);
}

void CouscousManager::onClientRequestSetPosition(double pos_x_m, double pos_y_m,
                                                 double orientation_rad) {
  posi_->setPosition(pos_x_m, pos_y_m, orientation_rad);
};

void CouscousManager::start() {
  int encoder1 = 0;
  int encoder2 = 0;

  while (true) {
    posi_->updatePosition(encoder1, encoder2);

    double abs_pos_x_m = 0;
    double abs_pos_y_m = 0;
    double abs_orientation_rad = 0;

    posi_->getPosition(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);

    // Trigger new position
    onPosiPositionUpdate(abs_pos_x_m, abs_pos_y_m, abs_orientation_rad);

    std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));

    encoder1 += 10;
    encoder2 += 10;
  }
}