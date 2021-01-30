#include <iostream>
#include <memory>

#include "CouscousManagerGui.h"
#include "HalSimu.h"
#include "Posi.h"
#include "RealTime.h"
#include "WebServer.h"

int main(int argc, char *argv[]) {
    auto couscousManager = std::make_shared<CouscousManagerGui>(std::make_shared<HalSimu>());
    couscousManager->start();

    return 0;
}