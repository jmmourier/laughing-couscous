#ifndef HALI_H
#define HALI_H

enum MotorIdEnum { motor1, motor2 };

class Hali {
   public:
    virtual void updater() = 0;

    virtual int getMd25Revision() = 0;
    virtual int getBatteryVoltage() = 0;
    virtual int getEncoder(MotorIdEnum id_motor) = 0;

    virtual void setMd25Speed(int speed_1, int speed_2) = 0;

   private:
};

#endif  // HALI_H
