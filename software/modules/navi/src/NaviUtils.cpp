#include "NaviUtils.h"

#include <math.h>

#include <cmath>
#include <iostream>
/**
 * origin: 0,0 is top left.
 * angle: clockwise = angle decrease
 */

double getDistanceToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    return hypot(
        std::abs(target_pos.pos_x - robot_pos.pos_x),
        std::abs(target_pos.pos_y - robot_pos.pos_y));
}

/** return angle between robot orientation and target point */
double shortcut_getAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    double targetAngle = getAngleBetweenTwoPoints(
        robot_pos.pos_x,
        robot_pos.pos_y,
        target_pos.pos_x,
        target_pos.pos_y);
    double angleToTarget = getAngleBetweenTwoAngles(robot_pos.orientation, targetAngle);
    return angleToTarget;
}

rotdir getRotationDir(const double robot_orientation, const double target_orientation) {
    double angleFromRobot = getAngleBetweenTwoAngles(robot_orientation, target_orientation);
    double shortestAngle = getShortestAngle(angleFromRobot);
    return getRotationDir(shortestAngle);
}

/**
 * @brief Get the Angle Between Two Angles object
 * @return double angle between robot orientation and angle to target
 */
double getAngleBetweenTwoAngles(const double &robot_orientation, const double &angle_to_target) {
    double angle = -robot_orientation + angle_to_target;
    return angle;
}

/**
 * @brief Get the Shortest Angle object
 */
double getShortestAngle(const double &angle) {
    double final_angle = angle + (1000 * M_PI);
    final_angle = fmod(final_angle, (2.f * M_PI));
    if (final_angle > M_PI) {
        final_angle = final_angle - (2 * M_PI);
    }
    return final_angle;
}

rotdir getRotationDir(const double &angle) {
    if (angle < 0.f) {
        return rotdir::Clockwise;
    } else {
        return rotdir::AntiClockwise;
    }
}
//////////////////////////////////////////////

/** retrun angle between robot position to target position
 */
double getAngleBetweenTwoPoints(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y) {
    double diff_x = target_pos_x - robot_pos_x;
    double diff_y = target_pos_y - robot_pos_y;
    double angle = atan2(diff_y, diff_x);
    return angle;
}

rotdir getRotationDir(const pos_info &robot_pos, const pos_info &target_pos) {
    double angleToTarget = getAngleBetweenTwoPoints(
        robot_pos.pos_x,
        robot_pos.pos_y,
        target_pos.pos_x,
        target_pos.pos_y);
    double angleFromRobot = getAngleBetweenTwoAngles(robot_pos.orientation, angleToTarget);
    double shortestAngle = getShortestAngle(angleFromRobot);
    return getRotationDir(shortestAngle);
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
            angle = -(2 * M_PI) + angle;
        } else {
            angle = (2 * M_PI) + angle;
        }
    }
    // std::cout << "getAngleDiff= " << angle << std::endl;
    return angle;
}

double getDistanceToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y) {
    return hypot(std::abs(target_pos_x - robot_pos_x), std::abs(target_pos_y - robot_pos_y));
}
