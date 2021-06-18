#ifndef COUSCOUS_NAVI_H
#define COUSCOUS_NAVI_H

#include <spdlog/logger.h>

#include <functional>
#include <memory>

#include "INaviRequestListener.h"
#include "NaviUtils.h"

class Navi {
   public:
    explicit Navi();
    void registerNaviRequestListener(const std::weak_ptr<INaviRequestListener> &navi_listener);
    // void publishToNaviSpeedRequestListeners(const int &motor1, const int &motor2) const;
    void publishToNaviSpeedRequestListeners(
        const float &v_x_mps,
        const float &v_y_mps,
        const float &omega_radps) const;
    void publishToNaviTargetReachedListeners(void) const;

    int setTargetPosition(
        const double &target_pos_x,
        const double &target_pos_y,
        const double &target_orientation);
    int setTargetOrientation(const float &orientation_rad);
    int setBackwardDistance(const double &dist);
    int setForwardDistance(const double &dist);
    int setCurrentPosition(
        const double &new_rob_pos_x,
        const double &new_rob_pos_y,
        const double &new_rob_orientation);

   private:
    void computeRegulatorSpeed(const pos_info &robot_pos, const pos_info &target_pos);
    void computeRotationSpeed(const double robot_orientation, const double target_orientation);
    void computeBackwardSpeed(
        const pos_info &current_robot_pos,
        const pos_info &previous_robot_pos);
    void computeForwardSpeed(const pos_info &current_robot_pos, const pos_info &previous_robot_pos);
    pos_info target_position_;
    pos_info actual_robot_position_;
    double backward_dist_;
    double forward_dist_;
    pos_info current_pos_before_backward_move_;
    pos_info current_pos_before_forward_move_;
    std::shared_ptr<spdlog::logger> logger_;
    std::vector<std::weak_ptr<INaviRequestListener>> navi_listeners_;
    // bool is_position_idle_ = true;
    // bool is_orientation_idle_ = true;
    enum action_in_progress { position, rotation, backward, forward, idle };
    action_in_progress action_in_progress_ = idle;
};

#endif  // COUSCOUS_NAVI_H
