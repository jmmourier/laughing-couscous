#include "WebServer.h"
#include <iostream>
#include <memory>

int main() {

  auto web_server = std::make_shared<WebServer>();

  web_server->start();

  return 0;
}
