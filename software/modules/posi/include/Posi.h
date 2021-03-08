#ifndef POSI_H
#define POSI_H

#include <spdlog/logger.h>

#include <memory>
#include <vector>

#include "IBaseTime.h"
#include "IPositionListener.h"

class Posi {
   public:
    explicit Posi(
        std::shared_ptr<IBaseTime> time_helper,
        double &start_pos_x,
        double &start_pos_y,
        double &start_orientation);

    void registerPositionListener(const std::weak_ptr<IPositionListener> &position_listener);

    void publishToListeners() const;

    /**
     * @brief Return abs position and orientation
     *
     * @param pos_x
     * @param pos_y
     * @param orientation
     */
    void getPosition(double &pos_x, double &pos_y, double &orientation) const;

    /**
     * @brief reset the position to a given point and orientation
     *
     * @param pos_x
     * @param pos_y
     * @param orientation
     */
    void setPosition(double pos_x, double pos_y, double orientation);

    /**
     * @brief Update the absolute position and orientation based on new encoders
     * value received from hali moodule
     *
     * @param encoder1 encoders of left wheel since last update
     * @param encoder2 encoders of right wheel since last update
     */
    void updatePosition(int encoder1, int encoder2);

   private:
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<IBaseTime> time_helper_;
    long previous_encoder1_;
    long previous_encoder2_;
    double abs_pos_x_;
    double abs_pos_y_;
    double orientation_;
    std::chrono::_V2::system_clock::time_point timestamp_;
    std::vector<std::weak_ptr<IPositionListener>> position_listeners_;
};

#endif  // POSI_H
