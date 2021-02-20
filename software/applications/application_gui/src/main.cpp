#include <iostream>
#include <memory>

#include "CouscousManagerGui.h"
#include "HalReal.h"
#include "Posi.h"
#include "RealTime.h"

int main(int argc, char *argv[]) {
    auto couscousManager = std::make_shared<CouscousManagerGui>(std::make_shared<HalReal>());
    couscousManager->start();

    return 0;
}