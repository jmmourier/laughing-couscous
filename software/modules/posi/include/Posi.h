#ifndef POSI_H
#define POSI_H

#include <spdlog/logger.h>

#include <memory>
#include <vector>

#include "IPositionListener.h"
#include "PositionOrientation.h"

class Posi {
   public:
    explicit Posi(const PositionOrientation &start_position_orientation);

    void registerPositionListener(const std::weak_ptr<IPositionListener> &position_listener);

    void publishToListeners() const;

    /**
     * @brief Return abs position and orientation
     *
     * @return const PositionOrientation
     */
    PositionOrientation getPosition() const;

    /**
     * @brief Reset the position to a given point and orientation
     *
     * @param position_orientation
     */
    void setPosition(const PositionOrientation &position_orientation);

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
    long previous_encoder1_;
    long previous_encoder2_;
    PositionOrientation position_orientation_;
    std::vector<std::weak_ptr<IPositionListener>> position_listeners_;
};

#endif  // POSI_H
