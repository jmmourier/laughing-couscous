#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "IHali.h"
#include "IHaliEncodersListener.h"
#include "IPositionListener.h"
#include "IWebServerRequestListener.h"
#include "Posi.h"
#include "WebServer.h"

class CouscousManager : public IPositionListener,
                        public IWebServerRequestListener,
                        public IHaliEncodersListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<IHali> &hali,
        const std::shared_ptr<Posi> &posi,
        const std::shared_ptr<WebServer> &web_server);

    void start();

    void onEncodersChanged(const int &encoders_motor1, const int &encoders_motor2) override;

    void onPositionChanged(
        const double &pos_x_m,
        const double &pos_y_m,
        const double &orientation_rad) override;

    void onWebServerPositionRequest(
        const double &pos_x,
        const double &pos_y,
        const double &orientation) override;
    void onWebServerSpeedRequest(const int &motor1, const int &motor2) override;
    void onWebServerTargetPositionRequest(const double &pos_x, const double &pos_y) override;

   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<IHali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::thread web_server_thread_;
};

#endif  // COUSCOUS_MANAGER_H