#include "CouscousManager.h"

#include "Hali.h"
#include "RealTime.h"

const static int INTERVAL_REFRESH_MS = 50;

void CouscousManager::start() {
    while (true) {
        int encoder1 = hali_->getEncoder(MotorIdEnum::motor1);
        int encoder2 = hali_->getEncoder(MotorIdEnum::motor2);

        posi_->updatePosition(encoder1, encoder2);

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
}