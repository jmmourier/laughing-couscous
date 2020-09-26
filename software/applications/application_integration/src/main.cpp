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

    // actions 
    for(;;){
        //update positioning
        cousous.posi_->updatePosition(couscous.hali_->getEncoder());

        //update mission        
        couscous.missi_->update(
            couscous.hali_->getBatteryVoltage();
            couscous.posi_->getPosition();
            // [...]
        );

        // update navigation/motion
        couscous.navi_->updateTarget(couscous.missi_->getNavigationTaget());
        couscous.hali_->setMd25Speed(couscous.navi_->getMotorSpeedTarget());

        // update interface 
        couscous.gui_->updateInterfacePosition(couscous.posi_->getPosition());
        couscous.gui_->updateInterfaceEncoder();
        couscous.gui_->updateInterfaceBattery();
        couscous.gui_->updateMissionStatus(couscous.missi_->getMissionStatus());

        std::this_thread::sleep_for(main_update_loop_time);
    }
    return 0;
}
