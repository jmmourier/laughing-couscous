#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <atomic>
#include <thread>

#include "IHali.h"
#include "IHaliListener.h"
#include "IPositionListener.h"
#include "IWebServerRequestListener.h"
#include "Missi.h"
#include "Moti.h"
#include "Navi.h"
#include "Posi.h"
#include "WebServer.h"
class CouscousManager : public IPositionListener,
                        public IWebServerRequestListener,
                        public INaviRequestListener,
                        public IHaliListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<IHali> &hali,
        const std::shared_ptr<Posi> &posi,
        const std::shared_ptr<WebServer> &web_server,
        const std::shared_ptr<Navi> &navi,
        const std::shared_ptr<Missi> &missi);

    void start();

    void onPositionChanged(const PositionOrientation &position_orientation) override;

    void onWebServerPositionRequest(const PositionOrientation &position_orientation) override;
    void onWebServerSpeedRequest(const int &motor1, const int &motor2) override;
    void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) override;
    void onWebServerTargetOrientationRequest(const float &orientation_rad) override;
    void onNaviTargetReachedRequest(void) override;
    void onNaviSpeedRequest(const float &v_x_mps, const float &v_y_mps, const float &omega_radps)
        override;
    void onGrabberStateChanged(const GrabberState &graberState) override;

   private:
    void runPreLaunchTest();
    const int INTERVAL_REFRESH_MS = 50;
    const int INTERVAL_REFRESH_BATTERY_MS = 1000;
    std::atomic<bool> is_robot_ready_;
    std::atomic<bool> pre_launch_test_done_;
    std::atomic<bool> mission_finished_;

    std::shared_ptr<Posi> posi_;
    std::shared_ptr<IHali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::shared_ptr<Missi> missi_;
    std::thread web_server_thread_;
    std::thread hali_thread_;
    std::shared_ptr<Navi> navi_;
    Moti moti_;
};

#endif  // COUSCOUS_MANAGER_H