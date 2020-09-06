#include "registry_element.h"
#include <iostream>

registry_element::registry_element() {
    empty=true;
    val = 0;
  //  std::cout<<"constructor registry field"<<std::endl;
}

void registry_element::setVal(int value){
    val = value;
    empty = false;
}

int registry_element::getVal(void){
    return val;
}

bool registry_element::isEmpty(void){
    return empty;
}