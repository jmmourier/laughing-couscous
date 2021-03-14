
#ifndef COUSCOUS_NAVISTATEMACHINE_H
#define COUSCOUS_NAVISTATEMACHINE_H

#include <functional>
#include <memory>
#include <vector>

#include "INaviRequestListener.h"
#include "NaviUtils.h"

#define DELTA_ANGLE_TO_STOP_ROTATION_MOVEMENT 0.01
#define DELTA_DIST_TO_STOP_FW_MOVEMENT 0.01

class NaviStateMachine {
   public:
    void registerNaviSMRequestListener(const std::weak_ptr<INaviRequestListener> &navi_listener);
    void publishToNaviSpeedRequestListeners(const int &motor1, const int &motor2) const;
    void publishToNaviTargetReachedListeners(void) const;

    enum NaviStateMachineEnum {
        ST0_IDLE,
        ST1_START_ALIGN_TO_TARGET,
        ST2_ALIGN_TO_TARGET,
        ST3_WAIT_FOR_MOVMENT,
        ST4_START_FW_MOVEMENT,
        ST5_DRIVING_TO_TARGET,
        ST9_DONE
    };
    /*  void naviStateMachineExec(
          const NaviStateMachineEnum execState,
          NaviStateMachineEnum next_state,
          pos_info robot_pos,
          pos_info target_pos);
  */
    NaviStateMachineEnum startAlignToTarget(pos_info robot_pos, pos_info target_pos);
    NaviStateMachineEnum alignToTarget(pos_info robot_pos, pos_info target_pos);
    NaviStateMachineEnum waitForMovement();
    NaviStateMachineEnum startFw();
    NaviStateMachineEnum drivingToTarget(pos_info robot_pos, pos_info target_pos);
    NaviStateMachineEnum waitForRotation();
    NaviStateMachineEnum startRotationToTargetOrientation(pos_info robot_pos, pos_info target_poss);
    NaviStateMachineEnum rotationToTargetOrientation(pos_info robot_pos, pos_info target_pos);
    NaviStateMachineEnum done();

    std::vector<std::weak_ptr<INaviRequestListener>> navi_listeners_;

   private:
};

#endif  // COUSCOUS_NAVISTATEMACHINE_H
