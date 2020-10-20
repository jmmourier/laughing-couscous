

#ifndef COUSCOUS_NAVIUTILS_H
#define COUSCOUS_NAVIUTILS_H

enum rotation_direction {Clockwise, AntiClockwise};
struct pos_info {
    double pos_x;
    double pos_y;
    double orientation;
};
typedef rotation_direction rotdir;
double get_reference_angle_to_target(pos_info robot_pos, pos_info target_pos);
double get_reference_angle_to_target(const double robot_pos_x, const double robot_pos_y, const double target_pos_x, const double target_pos_y);
double get_angle_to_target(const double robot_pos_x, const double robot_pos_y, const double robot_orientation, const double target_pos_x, const double target_pos_y);
double get_angle_difference(const double robot_orientation, const double target_orientation);
double get_angle_difference(const double robot_pos_x, const double robot_pos_y, const double robot_orientation, const double target_pos_x, const double target_pos_y);
double get_distance_to_target(const double robot_pos_x, const double robot_pos_y, const double target_pos_x, const double target_pos_y);
double get_distance_to_target(pos_info robot_pos, pos_info target_pos);
rotdir get_rotation_direction(const double robot_orientation, const double target_orientation);
#endif //COUSCOUS_NAVIUTILS_H
