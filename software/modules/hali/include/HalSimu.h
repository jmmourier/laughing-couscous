#ifndef HAL_SIMU_H
#define HAL_SIMU_H

#include "Hali.h"

class HalSimu : public Hali{
public :    
    HalSimu();

    void updater();
    
    int getMd25Revision();
    int getBatteryVoltage();
    int getEncoder(MotorIdEnum id_motor);

    void setMd25Speed(int speed1, int speed2);

private : 

};

#endif // HAL_SIMU_H