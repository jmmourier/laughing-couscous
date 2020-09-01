#include "Arduino.h"

enum motorId {
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
    void setSpeed(motorId id_motor_requested, int speed);
    void setAcceleration(char acceleration);

    void resetEncoder();

    bool hasTimeOutArise();
    void clearTimeout();
    
    long getEncoder(motorId id_motor_requested);
    int getVoltage();
    int getCurrent(motorId id_motor_requested);

private:
    HardwareSerial* serial_port_;
    long encoder_motor1_ = 0;
    long encoder_motor2_ = 0;
    byte software_revision_ = 0;
    int voltage_ = 0;
    int current_motor1_ = 0;
    int current_motor2_ = 0;
    unsigned int timeout_duration_ = 1000;
    bool timeout_arose = false;
};
