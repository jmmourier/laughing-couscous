#include "md25/md25.h"
#include "md25/md25.cpp"

md25 md25_(Serial1);

void setup(){
    Serial1.begin(38400);
    Serial.begin(9600);
}

void loop(){
    md25_.updateElectricalData();
    delay(10);
    Serial.print("md25voltage:");
    Serial.print(md25_.getVoltage());
    Serial.println(";");
    delay(1000);
}
