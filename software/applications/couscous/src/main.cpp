
#include <memory>

#include "CouscousManager.h"
#include "HalSimu.h"
#include "RealTime.h"

int main(int argc, char *argv[]) {
    // Robot starting position
    double start_pos_x_m = 1;
    double start_pos_y_m = 1;
    double start_orientation_rad = 0;

    auto hali = std::make_shared<HalSimu>();

    auto posi = std::make_shared<Posi>(
        std::make_shared<RealTime>(),
        start_pos_x_m,
        start_pos_y_m,
        start_orientation_rad);

    auto web_server = std::make_shared<WebServer>();

    auto couscous_manager = std::make_shared<CouscousManager>(hali, posi, web_server);

    posi->registerPositionListener(couscous_manager);
    hali->registerSpeedListener(couscous_manager);
    web_server->registerWebServerRequestListener(couscous_manager);

    couscous_manager->start();
    return 0;
}