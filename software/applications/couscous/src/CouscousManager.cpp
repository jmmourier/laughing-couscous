
#include "CouscousManager.h"

#include "IHali.h"
#include "IHaliListener.h"
#include "Posi.h"

CouscousManager::CouscousManager(
    const std::shared_ptr<IHali> &hali,
    const std::shared_ptr<Posi> &posi,
    const std::shared_ptr<WebServer> &web_server,
    const std::shared_ptr<Navi> &navi,
    const std::shared_ptr<Missi> &missi)
    : hali_(hali),
      posi_(posi),
      navi_(navi),
      web_server_(web_server),
      missi_(missi) {
    web_server_thread_ = std::thread([&] { web_server_->start(); });

    // note : the file mission.json shall be present on the same path the app is executed
    missi->loadMissionFile();

    // this is temporary and shall be replaced by a a listener on the strart button on the robot
    missi_->actionHasBeenDone();
}

void CouscousManager::onPositionChanged(const PositionOrientation &position_orientation) {
    web_server_->setPosition(position_orientation);

    navi_->setCurrentPosition(
        position_orientation.x_m_,
        position_orientation.y_m_,
        position_orientation.orientation_rad_);

    Action nextAction = missi_->getCurrentAction();
    if (nextAction.type == WAIT) {
        std::cout << "[Missi]:wait" << std::endl;
        // wait timeout or mission is not started or mission is done
    } else if (nextAction.type == MOVE) {
        std::cout << "[Missi]:move" << nextAction.target_x << " " << nextAction.target_y
                  << std::endl;
        navi_->setTargetPosition(nextAction.target_x, nextAction.target_y, 0);
    } else if (nextAction.type == GRABBER) {
        std::cout << "[Missi]:grabber  : " << nextAction.grabber_state << std::endl;
        // define how this is read
        IHaliListener::GrabberState grabber_state = (nextAction.grabber_state.compare("open") == 0)
                                                        ? IHaliListener::GrabberState::grabberOpen
                                                        : IHaliListener::GrabberState::grabberClose;
        hali_->setGrabber(grabber_state);
    } else if (nextAction.type == TURN) {
        std::cout << "[Missi]:turning " << nextAction.angle << std::endl;
        // TODO this need to be implemented
        // navi_->setTargetRotation(nextAction.angle);
    } else if (nextAction.type == UNKNOWN) {
        std::cout << "[Missi]:unknow action" << missi_->actionTypeToString(nextAction.type)
                  << std::endl;
        // This is abnormal, let's skip to next action
        missi_->actionHasBeenDone();
    }
}

void CouscousManager::onWebServerPositionRequest(const PositionOrientation &position_orientation) {
    posi_->setPosition(position_orientation);
}

void CouscousManager::onWebServerSpeedRequest(const int &speed_motor1, const int &speed_motor2) {
    std::cout << "speed" << speed_motor1 << " " << speed_motor2 << std::endl;
    hali_->setMd25Speed(speed_motor1, speed_motor2);
}

// webserver send target position
void CouscousManager::onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) {
    navi_->setTargetPosition(pos_x, pos_y, 0);
}

// webserver send target rotation
void CouscousManager::onWebServerTargetOrientationRequest(const float &orientation_rad) {
    navi_->setTargetOrientation(orientation_rad);
};

void CouscousManager::onGrabberStateChanged(const GrabberState &graberState) {
    web_server_->setGrabberState(graberState == GrabberState::grabberOpen);
};

void CouscousManager::onNaviTargetReachedRequest(void) {
    Action current_action = missi_->getCurrentAction();
    if (current_action.type == MOVE) {
        missi_->actionHasBeenDone();
    }
}

// void CouscousManager::onNaviSpeedRequest(const int &speed_motor1, const int &speed_motor2) {
void CouscousManager::onNaviSpeedRequest(
    const float &v_x_mps,
    const float &v_y_mps,
    const float &omega_radps) {
    MotorSpeed motor_speed =
        moti_.getMotorSpeedFromBaseSpeed(BaseSpeed(v_x_mps, v_y_mps, omega_radps));
    hali_->setMd25Speed(motor_speed.speed_motor_1_, motor_speed.speed_motor_2_);
}

void CouscousManager::start() {
    hali_thread_ = std::thread([&] { hali_->updater(); });

    long rounds = 0;

    while (true) {
        auto encoders_motor1 = hali_->getEncoder(MotorIdEnum::motor1);
        auto encoders_motor2 = hali_->getEncoder(MotorIdEnum::motor2);

        posi_->updatePosition(encoders_motor1, encoders_motor2);

        if (rounds % (INTERVAL_REFRESH_BATTERY_MS / INTERVAL_REFRESH_MS) == 0) {
            web_server_->setBattery(static_cast<float>(hali_->getBatteryVoltage()) / 10);
        }

        rounds++;

        std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL_REFRESH_MS));
    }
    web_server_thread_.join();
    hali_thread_.join();
}