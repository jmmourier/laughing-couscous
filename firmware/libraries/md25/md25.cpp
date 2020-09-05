#include "md25.h"

// Values of 0 being sent using serial.write() have to be cast as a byte to stop them being misinterpereted as NULL
// This is a bug with arduino 1
#define CMD                 (byte)0x00              //  MD25 command byte of 0

#define WRITESP1            0x31                    // Byte writes speed to motor 1
#define WRITESP2            0x32                    // Byte writes speed to motor 1
#define WRITEACCEL          0x33                    // Byte writes a value of acceleration
#define RESETREG            0x35                    // Byte resets encoders
#define SETMODE             0x34                    // Byte sets mode
#define READIVS             0x2C                    // Byte reads motor currents and battery voltage        
#define READENCS            0x25                    // Byte reads both encoders
#define GET_VER             0x29


md25::md25(HardwareSerial &serial_port){
    serial_port_ = &serial_port;
}

void md25::setTimeout(unsigned int timeout_duration){
    timeout_duration_ = timeout_duration;
}

void md25::updateEncorder(){
    long encoder_motor1 = 0; 
    long encoder_motor2 = 0;
    serial_port_->write(CMD);
    serial_port_->write(READENCS);
    unsigned long begin_request = millis();
    while(serial_port_->available() < 8){
        if(millis()-begin_request>timeout_duration_){
            timeout_arose = true;
            return;
        }
    }          // Wait for 8 bytes, first 4 encoder 1 values second 4 encoder 2 values 
    
    encoder_motor1 = serial_port_->read();                 // First byte for encoder 1, HH.
    encoder_motor1 <<= 8;
    encoder_motor1 += serial_port_->read();                // Second byte for encoder 1, HL
    encoder_motor1 <<= 8;
    encoder_motor1 += serial_port_->read();                // Third byte for encoder 1, LH
    encoder_motor1 <<= 8;
    encoder_motor1  += serial_port_->read();               // Fourth byte for encoder 1, LL

    encoder_motor2 = serial_port_->read();
    encoder_motor2 <<= 8;
    encoder_motor2 += serial_port_->read();
    encoder_motor2 <<= 8;
    encoder_motor2 += serial_port_->read();
    encoder_motor2 <<= 8;
    encoder_motor2 += serial_port_->read();

    encoder_motor1_ = encoder_motor1;
    encoder_motor2_ = encoder_motor2;
}

void md25::updateElectricalData(){
    serial_port_->write(CMD);
    serial_port_->write(READIVS);
    unsigned long begin_request = millis();
    while(serial_port_->available() < 3){
        if(millis()-begin_request>timeout_duration_){
            timeout_arose = true;
            return;
        }
    } 
    voltage_ = serial_port_->read();
    current_motor1_ = serial_port_->read();
    current_motor2_ = serial_port_->read();
}

void md25::updateRevision(){
    serial_port_->write(CMD);                                            // Get software version of MD25
    serial_port_->write(GET_VER);
    unsigned long begin_request = millis();
    while(serial_port_->available() < 1){
        if(millis()-begin_request>timeout_duration_){
            timeout_arose = true;
            return;
        }
    }                               // Wait for byte to become available         
    software_revision_ = serial_port_->read();
}

void md25::setMode(char mode){
    serial_port_->write(CMD);
    serial_port_->write(SETMODE);
    mode = max(mode,0);
    mode = min(mode,3);
    serial_port_->write(mode);
}

void md25::setSpeed(motorId id_motor_requested, int speed){
    serial_port_->write(CMD);
    if (id_motor_requested ==  motor1)
    {
        serial_port_->write(WRITESP1);
    }
    else // motor2
    {
        serial_port_->write(WRITESP2);
    }
    speed = max(speed,0);
    speed = min(speed,255);
    serial_port_->write(speed);
}

void md25::setAcceleration(char acceleration){
    acceleration = max(acceleration,1);
    acceleration = min(acceleration,10);
    serial_port_->write(CMD);
    serial_port_->write(WRITEACCEL);
    serial_port_->write(acceleration);
}

void md25::resetEncoder(){
    serial_port_->write(CMD);
    serial_port_->write(RESETREG);
}

bool md25::hasTimeOutArise(){
    return timeout_arose;
}

void md25::clearTimeout(){
    timeout_arose = false;
}

long md25::getEncoder(motorId id_motor_requested){
    if (id_motor_requested ==  motor1)
    {
        return encoder_motor1_;
    }
    else // motor2
    {
        return encoder_motor2_;
    }
}

int md25::getVoltage(){
    return voltage_;
}

int md25::getCurrent(motorId id_motor_requested){
    if (id_motor_requested ==  motor1)
    {
        return current_motor1_;
    }
    else // motor2
    {
        return current_motor2_;
    }
}
