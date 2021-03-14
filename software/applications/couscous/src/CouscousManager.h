#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "IHali.h"
#include "IHaliSpeedListener.h"
#include "IPositionListener.h"
#include "IWebServerListener.h"
#include "Posi.h"
#include "WebServer.h"

class CouscousManager : public IPositionListener,
                        public IWebServerListener,
                        public IHaliSpeedListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<IHali> &hali,
        const std::shared_ptr<Posi> &posi,
        const std::shared_ptr<WebServer> &web_server);

    void start();

    void onPositionChanged(
        const double &pos_x_m,
        const double &pos_y_m,
        const double &orientation_rad) override;

    void onPositionRequested(
        const double &pos_x_m,
        const double &pos_y_m,
        const double &orientation_rad) override;

    void onSpeedRequested(const int &speed_motor1, const int &speed_motor2) override;

    void onTargetPositionRequested(const double &pos_x, const double &pos_y) override;

    void onSpeedChanged(const int &motor1, const int &motor2) override;

   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<IHali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::thread web_server_thread_;
};

#endif  // COUSCOUS_MANAGER_H