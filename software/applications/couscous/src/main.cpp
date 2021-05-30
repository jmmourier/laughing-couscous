
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "CouscousManager.h"
#include "HalReal.h"
#include "HalSimu.h"
#include "IHali.h"

int main(int argc, char *argv[]) {
    // Robot starting position
    PositionOrientation start_position_orientation(1, 1, 0);

    std::shared_ptr<IHali> hali;

    (argc > 1 && std::strcmp(argv[1], "--halreal") == 0) ? hali = std::make_shared<HalReal>()
                                                         : hali = std::make_shared<HalSimu>();

    auto posi = std::make_shared<Posi>(start_position_orientation);
    auto web_server = std::make_shared<WebServer>();

    auto navi = std::make_shared<Navi>();
    auto missi = std::make_shared<Missi>();
    auto couscous_manager = std::make_shared<CouscousManager>(hali, posi, web_server, navi, missi);

    posi->registerPositionListener(couscous_manager);
    web_server->registerWebServerRequestListener(couscous_manager);
    navi->registerNaviRequestListener(couscous_manager);
    hali->registerHaliListener(couscous_manager);
    couscous_manager->start();
    return 0;
}