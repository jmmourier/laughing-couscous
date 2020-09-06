#ifndef SIMPLE_WEBSOCKET_SERVER_REGISTRY_H
#define SIMPLE_WEBSOCKET_SERVER_REGISTRY_H

#include "registry_element.h"
#include <string>

class registry {
public:
    enum registry_elements {avr_status, motor_R_speed, motor_L_speed, count};
    registry();
    void setReg(registry::registry_elements e, int val);
    int getReg(registry::registry_elements e);
    void test();

private:
    registry_element rdata[count + 1];

};


#endif //SIMPLE_WEBSOCKET_SERVER_REGISTRY_H
