#ifndef MD25_H
#define MD25_H

#include "Arduino.h"

enum MotorIdEnum {
    motor1,
    motor2
};

class md25{
public :
    md25(HardwareSerial &serial_port);
    void setTimeout(unsigned int timeout_duration);
    void updateEncorder();
    void updateElectricalData();
    void updateRevision();

    void setMode(char mode);
    void setSpeed(MotorIdEnum id_motor_requested, int speed);
    void setAcceleration(char acceleration);

    void resetEncoder();

    bool hasTimeOutArise();
    void clearTimeout();
    
    long getEncoder(MotorIdEnum id_motor_requested);
    int getVoltage();
    int getCurrent(MotorIdEnum id_motor_requested);

private:
    HardwareSerial* serial_port_;
    long encoder_motor1_ = 0;
    long encoder_motor2_ = 0;
    byte software_revision_ = 0;
    int voltage_ = 0;
    int current_motor1_ = 0;
    int current_motor2_ = 0;
    unsigned int timeout_duration_ = 50;
    bool timeout_arose = false;
};

#endif //MD25_H