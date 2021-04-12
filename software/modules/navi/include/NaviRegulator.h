
#ifndef COUSCOUS_NAVIREGULATOR_H
#define COUSCOUS_NAVIREGULATOR_H

#include <functional>
#include <memory>
#include <vector>

//#include "INaviRequestListener.h"
#include "NaviUtils.h"

class NaviStateMachine {
   public:
    int setCurrentPosition(
        const double &new_rob_pos_x,
        const double &new_rob_pos_y,
        const double &new_rob_orientation);

   private:
};

#endif  // COUSCOUS_NAVIREGULATOR_H