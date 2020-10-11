#include <thread>

#include "Hali.h"
#include "HalSimu.h"
#include "HalReal.h"

class Couscous
{
public:
    Couscous();
    Hali* hali_;
    //WebServer* web_server_;
    //Posi* posi_;
    //Navi* navi_;
    //Missi missi_;
private:
};

Couscous::Couscous(){
    hali_ = new HalSimu();
}

int main(int argc, char const *argv[])
{
    Couscous couscous;

    // init modules 
    std::thread updater_thread(&Hali::updater,couscous.hali_);


    std::chrono::milliseconds main_update_loop_time(10); // or whatever

    // add callback for order form GUI

    // actions 
    for(;;){
        //update positioning
        couscous.posi_->updatePosition(couscous.hali_->getEncoder());
        
        //update mission        
        int batteryVoltage = couscous.hali_->getBattery();
        couscous.missi_->updateBattery(batteryVoltage);

        couscous.missi_->update(
            couscous.posi_->getPosition();
            couscous.navi_->hasPositionBeenReached();
            // [...]
            );
        couscous.missi_->setOder(couscous.gui->getRequestOrder());
        couscous.hali_->setSpeed(couscous.gui->getSpeedRequest());
        couscous.posi_->setPosition(couscous.gui->getPositionRequest());

        // update navigation/motion
        couscous.navi_->updateTarget(couscous.missi_->getNavigationTaget());
        couscous.moti->setBaseSpeed(couscous.navi->getBaseSpeed());
        couscous.hali_->setMd25Speed(couscous.moti->getMotorSpeed());
        
        // update interface 
        couscous.gui_->updateInterfacePosition(couscous.posi_->getPosition());
        couscous.gui_->updateInterfaceEncoder();
        couscous.gui_->updateInterfaceBattery();
        couscous.gui_->updateInterfaceMissionStatus(couscous.missi_->getMissionStatus());

        std::this_thread::sleep_for(main_update_loop_time);
    }
    return 0;
}

