#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "IHali.h"
#include "IPositionListener.h"
#include "IWebServerRequestListener.h"
#include "Posi.h"
#include "WebServer.h"

class CouscousManager : public IPositionListener, public IWebServerRequestListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<IHali> &hali,
        const std::shared_ptr<Posi> &posi,
        const std::shared_ptr<WebServer> &web_server);

    void start();

    void onPositionChanged(const PositionOrientation &position_orientation) override;

    void onWebServerPositionRequest(const PositionOrientation &position_orientation) override;
    void onWebServerSpeedRequest(const int &motor1, const int &motor2) override;
    void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) override;

   private:
    const int INTERVAL_REFRESH_MS = 50;
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<IHali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::thread web_server_thread_;
    std::thread hali_thread_;
};

#endif  // COUSCOUS_MANAGER_H