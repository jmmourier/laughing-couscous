#include "CouscousManager.h"
#include "Posi.h"
#include "RealTime.h"
#include "WebServer.h"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {

  auto couscousManager = std::make_shared<CouscousManager>();
  couscousManager->start();

  return 0;
}