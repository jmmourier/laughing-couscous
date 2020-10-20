#include <iostream>
#include <memory>

#include "CouscousManager.h"
#include "Posi.h"
#include "RealTime.h"
#include "WebServer.h"

int main(int argc, char *argv[]) {
    auto couscousManager = std::make_shared<CouscousManager>();
    couscousManager->start();

    return 0;
}