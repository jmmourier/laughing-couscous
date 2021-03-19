#include "Posi.h"

#include <spdlog/logger.h>

#include <cmath>

#include "IPositionListener.h"
#include "logger/LoggerFactory.h"

const int TICKS_PER_ROTATION = 360;
const float SPACE_BETWEEN_WHEELS = 0.2;
const float WHEEL_RADIUS_M = 0.1;
const float WHEEL_PERIMETER = M_PI * 2 * WHEEL_RADIUS_M;

Posi::Posi(
    std::shared_ptr<IBaseTime> time_helper,
    const PositionOrientation &start_position_orientation)
    : logger_(LoggerFactory::registerOrGetLogger("Posi", spdlog::level::level_enum::debug)),
      time_helper_(std::move(time_helper)),
      previous_encoder1_(0),
      previous_encoder2_(0),
      position_orientation_(start_position_orientation),
      timestamp_(time_helper_->getNow()) {}

void Posi::registerPositionListener(const std::weak_ptr<IPositionListener> &position_listener) {
    position_listeners_.push_back(position_listener);
}

void Posi::publishToListeners() const {
    for (auto const &position_listener_ptr : position_listeners_) {
        if (auto position_listener = position_listener_ptr.lock()) {
            position_listener->onPositionChanged(position_orientation_);
        }
    }
}

PositionOrientation Posi::getPosition() const {
    return position_orientation_;
}

void Posi::setPosition(const PositionOrientation &position_orientation) {
    position_orientation_ = position_orientation;
}

void Posi::updatePosition(int encoder1, int encoder2) {
    auto time_now = time_helper_->getNow();

    // Diff since last updating position in second
    double delta_time_s =
        static_cast<double>(time_helper_->getDeltaTimeMS(time_now - timestamp_)) / 1000;

    // Reset timestamp
    timestamp_ = time_now;

    // Delta encoders
    auto delta_encoder1 = encoder1 - previous_encoder1_;
    auto delta_encoder2 = encoder2 - previous_encoder2_;

    // Linear speed
    float speed_left_wheel_ms = (WHEEL_PERIMETER * delta_encoder1 / TICKS_PER_ROTATION);
    float speed_right_wheel_ms = (WHEEL_PERIMETER * delta_encoder2 / TICKS_PER_ROTATION);

    // Average speed
    float average_speed = (speed_left_wheel_ms + speed_right_wheel_ms) / 2;

    // Delta positions
    float delta_position_x = std::cos(position_orientation_.orientation_rad_) * average_speed;
    float delta_position_y = std::sin(position_orientation_.orientation_rad_) * average_speed;

    // Delta orientation
    float delta_orientation = (speed_left_wheel_ms - speed_right_wheel_ms) / SPACE_BETWEEN_WHEELS;

    // Set new absolute positions and orientation
    position_orientation_.x_m_ = position_orientation_.x_m_ + delta_position_x * delta_time_s;
    position_orientation_.y_m_ = position_orientation_.y_m_ + delta_position_y * delta_time_s;
    position_orientation_.orientation_rad_ =
        position_orientation_.orientation_rad_ + delta_orientation * delta_time_s;

    // Update previous encoders with current ones
    previous_encoder1_ = encoder1;
    previous_encoder2_ = encoder2;

    SPDLOG_LOGGER_INFO(
        logger_,
        "Update position x: {} - y: {} - orientation: {}",
        position_orientation_.x_m_,
        position_orientation_.y_m_,
        position_orientation_.orientation_rad_);

    // Publish new position to position listeners
    publishToListeners();
}