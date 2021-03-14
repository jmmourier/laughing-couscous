#include "NaviUtils.h"

#include <cmath>
#include <iostream>

/**
 * angle between two points (base reference)
 * angle between one point and
 */

/**
 *
 * @param robot_pos_x
 * @param robot_pos_y
 * @param target_pos_x
 * @param target_pos_y
 * @return angle between robot pos and target pos.
 */
double getReferenceAngleToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y) {
    double diff_x = (target_pos_x - robot_pos_x);
    double diff_y = (target_pos_y - robot_pos_y);
    double angle = atan(diff_y / diff_x);

    if (diff_x < 0.f && diff_y > 0.f) {  // quarter 2
        angle = angle + M_PI;
    } else if (diff_x < 0.f && diff_y < 0.f) {  // quarter 3
        angle = angle + M_PI;
    } else if (diff_x > 0.f && diff_y < 0.f) {  // quarter 4
        angle = (2 * M_PI) + angle;
    }
    return angle;
}
double getReferenceAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    return getReferenceAngleToTarget(
        robot_pos.pos_x,
        robot_pos.pos_y,
        target_pos.pos_x,
        target_pos.pos_y);
}

/**
 *
 * @param robot_pos_x
 * @param robot_pos_y
 * @param robot_orientation
 * @param target_pos_x
 * @param target_pos_y
 * @return angle between robot orientation and target position
 */
double getAngleToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &robot_orientation,
    const double &target_pos_x,
    const double &target_pos_y) {
    double angle = getAngleDifference(
        robot_orientation,
        getReferenceAngleToTarget(robot_pos_x, robot_pos_y, target_pos_x, target_pos_y));
    // std::cout<<"angle="<<angle<<" ref="<<get_reference_angle_to_target(robot_pos_x, robot_pos_y,
    // target_pos_x, target_pos_y)<<std::endl;
    return angle;
}
double getAngleToTargetFrom(const pos_info &robot_pos, const pos_info &target_pos) {
    return getAngleToTarget(
        robot_pos.pos_x,
        robot_pos.pos_y,
        robot_pos.orientation,
        target_pos.pos_x,
        target_pos.pos_y);
}
/**
 * Compute shortest angle between two angles
 * @param robot_orientation
 * @param target_orientation
 * @return shortest angle bewteen two angles
 */
double getAngleDifference(const double &robot_orientation, const double &target_orientation) {
    double angle = target_orientation - robot_orientation;
    if (std::abs(angle) > M_PI) {
        if (angle > 0) {
            angle = (2 * M_PI) - angle;
        } else {
            angle = (2 * M_PI) + angle;
        }
    }
    return angle;
}

double getAngleDifference(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &robot_orientation,
    const double &target_pos_x,
    const double &target_pos_y) {
    return getAngleDifference(
        robot_orientation,
        getAngleToTarget(robot_pos_x, robot_pos_y, robot_orientation, target_pos_x, target_pos_y));
}

/**
 * Special case, on identical angles, return clockwise.
 * @param robot_orientation
 * @param target_orientation
 * @return
 */
rotdir getRotationDirection(const double &robot_orientation, const double &target_orientation) {
    double angle = getAngleDifference(robot_orientation, target_orientation);
    if (angle > 0) {
        return rotdir::AntiClockwise;
    } else {
        return rotdir::Clockwise;
    }
}
double getDistanceToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y) {
    return hypot(std::abs(target_pos_x - robot_pos_x), std::abs(target_pos_y - robot_pos_y));
}

double getDistanceToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    // std::cout<<"rob x:"<<robot_pos.pos_x<<" rob y:"<<robot_pos.pos_y<<" targ
    // x:"<<target_pos.pos_x<<" targ y:"<<target_pos.pos_y<<std::endl; std::cout<<"hyp:
    // "<<hypot(abs(target_pos.pos_x - robot_pos.pos_x), abs(target_pos.pos_y-robot_pos.pos_y))<<"
    // x="<<std::abs(target_pos.pos_x - robot_pos.pos_x)<<std::endl;
    return hypot(
        std::abs(target_pos.pos_x - robot_pos.pos_x),
        std::abs(target_pos.pos_y - robot_pos.pos_y));
}
