#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "IHali.h"
#include "IPositionListener.h"
#include "IWebServerRequestListener.h"
#include "Moti.h"
#include "Navi.h"
#include "Posi.h"
#include "WebServer.h"
class CouscousManager : public IPositionListener,
                        public IWebServerRequestListener,
                        public INaviRequestListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<IHali> &hali,
        const std::shared_ptr<Posi> &posi,
        const std::shared_ptr<WebServer> &web_server,
        const std::shared_ptr<Navi> &navi);

    void start();

    void onPositionChanged(const PositionOrientation &position_orientation) override;

    void onWebServerPositionRequest(const PositionOrientation &position_orientation) override;
    void onWebServerSpeedRequest(const int &motor1, const int &motor2) override;
    void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) override;
    void onNaviTargetReachedRequest(void) override;
    void onNaviSpeedRequest(const float &v_x_mps, const float &v_y_mps, const float &omega_radps)
        override;

   private:
    const int INTERVAL_REFRESH_MS = 50;
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<IHali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::thread web_server_thread_;
    std::thread hali_thread_;
    std::shared_ptr<Navi> navi_;
    Moti moti_;
};

#endif  // COUSCOUS_MANAGER_H