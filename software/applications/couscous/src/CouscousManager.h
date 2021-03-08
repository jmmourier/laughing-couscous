#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "Hali.h"
#include "IPositionListener.h"
#include "IWebServerListener.h"
#include "Posi.h"
#include "WebServer.h"

class CouscousManager : public IPositionListener, public IWebServerListener {
   public:
    explicit CouscousManager(
        const std::shared_ptr<Hali> &hali,
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

   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<Hali> hali_;
    std::shared_ptr<WebServer> web_server_;
    std::thread web_server_thread_;
};

#endif  // COUSCOUS_MANAGER_H