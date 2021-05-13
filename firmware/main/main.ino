#include "Flag/Flag.cpp"
#include "GameTimer/GameTimer.cpp"
#include "Grabber/Grabber.cpp"
#include "Leds/Leds.cpp"
#include "Md25/Md25.cpp"
#include "MessageParser/MessageParser.cpp"
#include "Switches/Switches.cpp"
#include "Srf02/Srf02.cpp"

int pin_grabber_ = 4;
Grabber grabber_(pin_grabber_);
unsigned long grabber_last_update_ = 0;
unsigned int grabber_timer_ = 300;  // ms

MessageParser message_parser_;
const int buffer_size = 80;
char buffer_[buffer_size];
int buffer_fullfillness = 0;

md25 md25_(Serial1);
unsigned long md25_last_update_ = 0;
unsigned int md25_timer_ = 300;  // ms

int pin_flag_ = 5;
Flag flag_(pin_flag_);
bool is_flag_up_ = false;
unsigned long flag_check_last_update_ = 0;
unsigned long flag_check_timer_ = 300;

int pin_switch_1_ = 7;
int pin_switch_2_ = 9;
Switches switches_(pin_switch_1_, pin_switch_2_);
unsigned long switches_last_update_ = 0;
unsigned long switches_timer_ = 300;

int pin_led_green_ = 10;
int pin_led_red_ = 16;
Leds leds_(pin_led_green_, pin_led_red_);
unsigned long leds_last_update_ = 0;
unsigned long leds_timer_ = 30;

GameTimer game_timer_;
bool is_game_finished = false;
unsigned long is_game_finished_last_update_ = 0;
unsigned long is_game_finished_timer_ = 300;

int pin_start_switch_ = 14;
unsigned long start_switch_last_update_ = 0;
unsigned long start_switch_timer_ = 100;

Srf02 srf02_;
unsigned long srf02_last_update_ = 0;
unsigned long srf02_timer_ = 30;
unsigned long srf02_send_value_last_update_ = 0;
unsigned long srf02_send_value_timer_ = 100;


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

    pinMode(pin_start_switch_,INPUT);

    leds_.setStatus(waiting);

    srf02_.init();
}

void loop() {

    readSerial();

    updateMd25();

    updateGrabber();

    updateFlag();

    checkStartButtonAndSendStatus();

    updateEndGame();

    checkSwitchesAndSendStatus();

    updateLeds();

    srf02Update();

}

void readSerial() {
    if (Serial.available()) {
        unsigned char input_char = Serial.read();
        buffer_[buffer_fullfillness] = input_char;
        buffer_fullfillness++;
        if (buffer_fullfillness >= buffer_size) {
            memset(buffer_, 0, sizeof(buffer_));
            buffer_fullfillness = 0;
        }
        if (input_char == message_parser_.getEndChar()) {
            CommandData command_data = message_parser_.parse(buffer_);
            HandleCommands(command_data);
            memset(buffer_, 0, sizeof(buffer_));
            buffer_fullfillness = 0;
        }
    }
}

void HandleCommands(CommandData command_data) {
    if (command_data.command_ == speedMotor1 &&
        is_game_finished == false) {
        md25_.setSpeed(motor1, command_data.argument_);
    } else if (command_data.command_ == speedMotor2 &&
        is_game_finished == false) {
        md25_.setSpeed(motor2, command_data.argument_);
    } else if (command_data.command_ == versionRevisionRequested) {
        md25_.updateRevision();
        delay(10);
        Serial.print("md25version:");
        Serial.print(md25_.getRevision());
        Serial.println(";");
    } else if (command_data.command_ == resetEncoder) {
        md25_.resetEncoder();
        delay(10);
    } else if (command_data.command_ == grabberPositionRequested &&
        is_game_finished == false) {
        if (command_data.argument_ == grabberOpened) {
            grabber_.open();
        } else if (command_data.argument_ == grabberClosed) {
            grabber_.close();
        }
    }
}

void updateMd25(){
    if (millis() - md25_last_update_ > md25_timer_) {
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
    md25_last_update_ = millis();
    }
}

void updateGrabber(){
    if (millis() - grabber_last_update_ > grabber_timer_) {
        Serial.print("grabberState:");
        Serial.print(grabber_.getGrabber());
        Serial.println(";");
        grabber_last_update_ = millis();
    }
}

void updateFlag(){
    if(millis()- flag_check_last_update_ > flag_check_timer_) {
        if(game_timer_.hasTimerReached(95000)){
            flag_.setFlag(flagUp);
        }
        else{
            flag_.setFlag(flagDown);
        }
        flag_check_last_update_ = millis();
    }
}

void updateEndGame(){
    if (millis() - is_game_finished_last_update_ > is_game_finished_timer_) {
        if(game_timer_.hasTimerReached(100000)){
            md25_.setSpeed(motor1, 128);
            md25_.setSpeed(motor2, 128);
            is_game_finished = true;
            leds_.setStatus(done);
        }
        is_game_finished_last_update_ = millis();
    }
}

void checkStartButtonAndSendStatus(){
    if (millis() - start_switch_last_update_ > start_switch_timer_) {
        
        bool robot_is_started = digitalRead(pin_start_switch_);

        if(robot_is_started){ // started
            if(!game_timer_.isTimerCounting()){
                game_timer_.start();
                leds_.setStatus(running);
            }
        } else { // not started
            game_timer_.reset();
            leds_.setStatus(waiting);
            is_game_finished = false;
        }
        
        Serial.print("robotStarted:");
        Serial.print(robot_is_started);
        Serial.println(";");

        start_switch_last_update_ = millis();
    }
}

void checkSwitchesAndSendStatus(){
    if (millis() - switches_last_update_ > switches_timer_) {
        
        switches_.updateSwitches();

        Serial.print("switch1:");
        Serial.print(switches_.getSwitch(switch_id_1));
        Serial.println(";");

        Serial.print("switch2:");
        Serial.print(switches_.getSwitch(switch_id_2));
        Serial.println(";");

        switches_last_update_ = millis();
    }
}

void updateLeds(){
    if (millis() - leds_last_update_ > leds_timer_) {
        leds_.updateLeds();
        leds_last_update_ = millis();
    }
}

void srf02Update(){
    if (millis() - srf02_last_update_ > srf02_timer_) {
        srf02_.updateSensor();
        srf02_last_update_ = millis();
    }
    if (millis() - srf02_send_value_last_update_ > srf02_send_value_timer_) {
        
        Serial.print("distance:");
        Serial.print(srf02_.getDistance());
        Serial.println(";");
        srf02_send_value_last_update_ = millis();
    }
}
