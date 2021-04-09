#include "Posi.h"

#include <spdlog/logger.h>

#include <cmath>

#include "IPositionListener.h"
#include "constant.h"
#include "logger/LoggerFactory.h"

Posi::Posi(const PositionOrientation &start_position_orientation)
    : logger_(LoggerFactory::registerOrGetLogger("Posi", spdlog::level::level_enum::info)),
      previous_encoder1_(0),
      previous_encoder2_(0),
      position_orientation_(start_position_orientation) {}

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
    // Delta encoders
    auto delta_encoder1 = encoder1 - previous_encoder1_;
    auto delta_encoder2 = encoder2 - previous_encoder2_;

    // Linear speed
    float speed_left_wheel_ms =
        (constant::wheel_perimeter_m * delta_encoder1 / constant::ticks_per_rotation);
    float speed_right_wheel_ms =
        (constant::wheel_perimeter_m * delta_encoder2 / constant::ticks_per_rotation);

    // Average speed
    float average_speed = (speed_left_wheel_ms + speed_right_wheel_ms) / 2;

    // Delta positions
    float delta_position_x = std::cos(position_orientation_.orientation_rad_) * average_speed;
    float delta_position_y = std::sin(position_orientation_.orientation_rad_) * average_speed;

    // Delta orientation
    float delta_orientation =
        -(speed_left_wheel_ms - speed_right_wheel_ms) / constant::wheel_distance_m_;

    // Set new absolute positions and orientation
    position_orientation_.x_m_ = position_orientation_.x_m_ + delta_position_x;
    position_orientation_.y_m_ = position_orientation_.y_m_ + delta_position_y;
    position_orientation_.orientation_rad_ =
        formatOrientationRad(position_orientation_.orientation_rad_ + delta_orientation);

    // Update previous encoders with current ones
    previous_encoder1_ = encoder1;
    previous_encoder2_ = encoder2;

    SPDLOG_LOGGER_INFO(
        logger_,
        "Update position x: {} y: {} orientation: {}",
        position_orientation_.x_m_,
        position_orientation_.y_m_,
        position_orientation_.orientation_rad_);

    // Publish new position to position listeners
    publishToListeners();
}

float Posi::formatOrientationRad(float orientation_rad) {
    float formatted_orientation_rad = std::fmod(orientation_rad, constant::whole_rotation_rad);

    if (formatted_orientation_rad < 0) {
        formatted_orientation_rad += constant::whole_rotation_rad;
    }

    return formatted_orientation_rad;
}