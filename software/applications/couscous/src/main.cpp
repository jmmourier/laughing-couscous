
#include <memory>

#include "CouscousManager.h"
#include "HalSimu.h"
#include "RealTime.h"

int main(int argc, char *argv[]) {
    // Robot starting position
    PositionOrientation start_position_orientation(1, 1, 0);

    auto hali = std::make_shared<HalSimu>();
    auto posi = std::make_shared<Posi>(std::make_shared<RealTime>(), start_position_orientation);
    auto web_server = std::make_shared<WebServer>();

    auto couscous_manager = std::make_shared<CouscousManager>(hali, posi, web_server);

    posi->registerPositionListener(couscous_manager);
    hali->registerEncodersListener(couscous_manager);
    web_server->registerWebServerRequestListener(couscous_manager);

    couscous_manager->start();
    return 0;
}