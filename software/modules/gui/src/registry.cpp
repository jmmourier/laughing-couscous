
#include "registry.h"
#include <iostream>

registry::registry() {
}

int registry::getReg(registry::registry_elements e){
    return rdata[e].getVal();
}

void registry::setReg(registry::registry_elements e, int val){
    rdata[e].setVal(val);
}

void registry::test(){
    rdata[avr_status].setVal(123);
    std::cout<<"data:"<<rdata[avr_status].getVal()<<std::endl;
    getReg(avr_status);
}

