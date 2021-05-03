#include "NaviUtils.h"

#include <math.h>

#include <cmath>
#include <iostream>
/**
 * origin: 0,0 is top left.
 * angle: clockwise = angle increase
 */

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

/** return angle between robot orientation and angle to target
 */
double getAngleBetweenTwoAngles(const double &robot_orientation, const double &angle_to_target) {
    double angle = -robot_orientation + angle_to_target;
    return angle;
}

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

rotdir getRotationDir(const double robot_orientation, const double target_orientation) {
    double angleFromRobot = getAngleBetweenTwoAngles(robot_orientation, target_orientation);
    double shortestAngle = getShortestAngle(angleFromRobot);
    return getRotationDir(shortestAngle);
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

///////////////////////////////////////////////////////////////////////
// old stuffs
//////////////////////////////////////////////////////////////////////

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

/**
 * Special case, on identical angles, return clockwise.
 * @param robot_orientation
 * @param target_orientation
 * @return
 */
rotdir getRotationDirection(const double &robot_orientation, const double &target_orientation) {
    double angle = getAngleDifference(robot_orientation, target_orientation);
    if (angle > 0) {
        return rotdir::Clockwise;
    } else {
        return rotdir::AntiClockwise;
    }
}

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
    double diff_x = target_pos_x - robot_pos_x;
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

/**
 * @brief Get the Reference Angle between robot position and target point.
 */
double getReferenceAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    return getReferenceAngleToTarget(
        robot_pos.pos_x,
        robot_pos.pos_y,
        target_pos.pos_x,
        target_pos.pos_y);
}

/**
 * @brief Get the angle between robot orientation and target point.
 *
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
    return angle;
}

/**
 * @brief Get the Angle between robot orientation and target point.
 *
 */
double getAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos) {
    return getAngleToTarget(
        robot_pos.pos_x,
        robot_pos.pos_y,
        robot_pos.orientation,
        target_pos.pos_x,
        target_pos.pos_y);
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
