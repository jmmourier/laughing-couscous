#include "Srf02.h"

Srf02::Srf02(){
    distance_cm_ = 0;
    is_measurment_ready_ = false;
    is_measurment_requested_ = false;
}

void Srf02::init(){
    Wire.begin();
}

void Srf02::updateSensor(){
    if(!is_measurment_requested_) {
        requestDistance();
    } else if(is_measurment_requested_ && !is_measurment_ready_) { 
        if(millis() - last_distance_requested_time_ > 70){
            is_measurment_ready_ = true;
        }
    } else if(is_measurment_requested_ && is_measurment_ready_){
        readDistance();
    } 
}

int Srf02::getDistance(){
    return distance_cm_;
}

void Srf02::requestDistance(){
    // instruct sensor to read echoes
    Wire.beginTransmission(112); // transmit to device #112 (0x70)
    // the address specified in the datasheet is 224 (0xE0)
    // but i2c adressing uses the high 7 bits so it's 112
    Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
    Wire.write(byte(0x51));      // command sensor to measure in "centimeters" (0x51)
    // use 0x51 for centimeters
    // use 0x52 for ping microseconds
    Wire.endTransmission();      // stop transmitting

    is_measurment_requested_ = true;
    last_distance_requested_time_ = millis();
}

void Srf02::readDistance(){
    // instruct sensor to return a particular echo reading
    Wire.beginTransmission(112); // transmit to device #112
    Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
    Wire.endTransmission();      // stop transmitting

    // step 4: request reading from sensor
    Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

    // step 5: receive reading from sensor
    if (2 <= Wire.available())   // if two bytes were received
    {
        distance_cm_ = 0;
        distance_cm_ = Wire.read();  // receive high byte (overwrites previous reading)
        distance_cm_ = distance_cm_ << 8;    // shift high byte to be high 8 bits
        distance_cm_ |= Wire.read(); // receive low byte as lower 8 bits
    } else {
        // TODO
    }

    is_measurment_requested_ = false;
    is_measurment_ready_ = false;
}