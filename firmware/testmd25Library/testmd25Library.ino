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
    md25_.updateEncorder();
    delay(10);
    Serial.print("md25voltage:");
    Serial.print(md25_.getVoltage());
    Serial.println(";");
    Serial.print("md25encoder1:");
    Serial.print(md25_.getEncoder(motor1));
    Serial.println(";");
    Serial.print("md25encoder2:");
    Serial.print(md25_.getEncoder(motor2));
    Serial.println(";");
    delay(1000);
    if(Serial.available()){
        Serial.print("Received:");
        while(Serial.available()){
            Serial.print(Serial.read());
        }
        Serial.print(";");
    }
}
