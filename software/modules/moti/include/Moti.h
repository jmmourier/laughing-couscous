#ifndef MOTI_H
#define MOTI_H

#include "constant.h"

struct MotorSpeed {
    MotorSpeed(int speed_motor_1, int speed_motor_2)
        : speed_motor_1_(speed_motor_1),
          speed_motor_2_(speed_motor_2){};
    int speed_motor_1_;
    int speed_motor_2_;
};

struct BaseSpeed {
    BaseSpeed(float v_x_mps, float v_y_mps, float omega_radps)
        : v_x_mps_(v_x_mps),
          v_y_mps_(v_y_mps),
          omega_radps_(omega_radps){};
    float v_x_mps_, v_y_mps_, omega_radps_;
};

class Moti {
   public:
    Moti();

    void setBaseSpeed(BaseSpeed base_speed);

    MotorSpeed getMotorSpeed();

    MotorSpeed getMotorSpeedFromBaseSpeed(BaseSpeed base_speed);

   private:
    float wheel_diameter_m_ = constant::wheel_diameter_m_;
    float wheel_distance_m_ = constant::wheel_distance_m_;
    float max_wheel_speed_radps_ = constant::max_wheel_speed_radps_;
    BaseSpeed base_speed_;
};

#endif  // MOTI_H