#ifndef MOTI_H
#define MOTI_H

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
    MotorSpeed getMotorSpeedFromBaseSpeed(BaseSpeed base_speed);

    void setWheelDiameter(float wheel_diameter_m);
    void setWheelDistance(float wheel_distance_m);
    void setMaxWheelSpeed(float max_wheel_speed_radps);

   private:
    float wheel_diameter_m_ = 0.100;
    float wheel_distance_m_ = 0.253;
    float max_wheel_speed_radps_ = 17.802;  // 170 rpm <> 17,802 radps
};

#endif  // MOTI_H