#include "Grabber/Grabber.cpp"
#include "Md25/Md25.cpp"
#include "Flag/Flag.cpp"
#include "Switches/Switches.cpp"
#include "Leds/Leds.cpp"
#include "GameTimer/GameTimer.cpp"

int pin_grabber_ = 4;
Grabber grabber_(pin_grabber_);

md25 md25_(Serial1);

int pin_flag_ = 5;
Flag flag_(pin_flag_);
bool is_flag_up_ = false;

int pin_switch_1_ = 7;
int pin_switch_2_ = 9;
Switches switches(pin_switch_1_, pin_switch_2_);

int pin_led_green_ = 10;
int pin_led_red_ = 16;
Leds leds_(pin_led_green_, pin_led_red_);

GameTimer game_timer_;

int pin_start_switch_ = 14;

unsigned long last_update_ = 0;

void setup() {
    Serial1.begin(38400);
    Serial.begin(9600);

    md25_.setMode(0);
    md25_.resetEncoder();

    grabber_.init();
    delay(10);
    grabber_.open();

    flag_.init();
    delay(10);
    flag_.setFlag(flagDown);

    leds_.setStatus(running);

    game_timer_.start();

    pinMode(pin_start_switch_, INPUT);
}

void loop() {


    leds_.updateLeds();
    switches.updateSwitches();

    if(game_timer_.hasTimerReached(15)){
        leds_.setStatus(done);
    }

    if(millis()-last_update_ > 2000 && !game_timer_.hasTimerReached(30000)) {
        last_update_ = millis();
        // update md25
        md25_.updateElectricalData();
        delay(10);
        md25_.updateEncorder();
        delay(10);

        // switch grabber state
        if (grabber_.getGrabber() == grabberOpened) {
            grabber_.close();
        } else {
            grabber_.open();
        }

        if(is_flag_up_) {
            flag_.setFlag(flagDown);
            is_flag_up_ = false;
        } else {
            flag_.setFlag(flagUp);
            is_flag_up_ = true;
        }

        printStatus();
    }

    delay(50);
}

void printStatus() {

    Serial.print("md25voltage:");
    Serial.print(md25_.getVoltage());
    Serial.println(";");
    Serial.print("md25encoder1:");
    Serial.print(md25_.getEncoder(motor1));
    Serial.println(";");
    Serial.print("md25encoder2:");
    Serial.print(md25_.getEncoder(motor2));
    Serial.println(";");


    Serial.print("switch 1:");
    Serial.print(switches.getSwitch(switch_id_1));
    Serial.println(";");
    Serial.print("switch 2:");
    Serial.print(switches.getSwitch(switch_id_2));
    Serial.println(";");

    Serial.print("start pin :");
    Serial.print(digitalRead(pin_start_switch_));
    Serial.println(";");

    
    
}