

#ifndef COUSCOUS_NAVIUTILS_H
#define COUSCOUS_NAVIUTILS_H

enum rotation_direction { Clockwise, AntiClockwise };
struct pos_info {
    double pos_x;
    double pos_y;
    double orientation;
};

typedef rotation_direction rotdir;

double getAngleBetweenTwoPoints(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y);

double getAngleBetweenTwoAngles(const double &robot_orientation, const double &angle_to_target);

double getShortestAngle(const double &angle);
rotdir getRotationDir(const double &angle);
rotdir getRotationDir(const pos_info &robot_pos, const pos_info &target_pos);
double shortcut_getAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos);

/////old stuffs /////

double getReferenceAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos);

double getReferenceAngleToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y);

double getAngleToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &robot_orientation,
    const double &target_pos_x,
    const double &target_pos_y);

double getAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos);

double getAngleDifference(const double &robot_orientation, const double &target_orientation);

double getAngleDifference(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &robot_orientation,
    const double &target_pos_x,
    const double &target_pos_y);

double getDistanceToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y);

double getDistanceToTarget(const pos_info &robot_pos, const pos_info &target_pos);

rotdir getRotationDirection(const double &robot_orientation, const double &target_orientation);
#endif  // COUSCOUS_NAVIUTILS_H
