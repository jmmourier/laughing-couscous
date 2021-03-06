

#ifndef COUSCOUS_NAVIUTILS_H
#define COUSCOUS_NAVIUTILS_H

enum rotation_direction { Clockwise, AntiClockwise };
struct pos_info {
    double pos_x;
    double pos_y;
    double orientation;
};

typedef rotation_direction rotdir;

double getDistanceToTarget(const pos_info &robot_pos, const pos_info &target_pos);
double shortcut_getAngleToTarget(const pos_info &robot_pos, const pos_info &target_pos);
rotdir getRotationDir(const double robot_orientation, const double target_orientation);
rotdir getRotationDir(const double &angle);
double getAngleBetweenTwoAngles(const double &robot_orientation, const double &angle_to_target);
double getShortestAngle(const double &angle);

double getAngleBetweenTwoPoints(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y);

rotdir getRotationDir(const pos_info &robot_pos, const pos_info &target_pos);

double getAngleDifference(const double &robot_orientation, const double &target_orientation);

double getDistanceToTarget(
    const double &robot_pos_x,
    const double &robot_pos_y,
    const double &target_pos_x,
    const double &target_pos_y);

rotdir getRotationDirection(const double &robot_orientation, const double &target_orientation);

#endif  // COUSCOUS_NAVIUTILS_H
