#include "MessageParser/MessageParser.cpp"
#include "Md25/Md25.cpp"

MessageParser message_parser;
const int buffer_size = 80;
char buffer_[buffer_size];
int buffer_fullfillness = 0;

md25 md25_(Serial1);
unsigned long md25_update_time = 0;
unsigned int md25_delay_update = 300; // ms

void setup() {
    Serial1.begin(38400);
    Serial.begin(9600);
}

void loop() {


    if(Serial.available()){
        unsigned char input_char = Serial.read();
        buffer_[buffer_fullfillness] = input_char;
        buffer_fullfillness++;
        if(buffer_fullfillness >= buffer_size){
            memset(buffer_, 0, sizeof(buffer_));
            buffer_fullfillness = 0;
        }
        if(input_char == message_parser.getEndChar()){
            CommandData command_data = message_parser.parse(buffer_);
            memset(buffer_, 0, sizeof(buffer_));
            buffer_fullfillness = 0;

            // Serial.print("parsed command id : ");
            // Serial.print(command_data.command_);
            // Serial.print(" argument : ");
            // Serial.print(command_data.argument_,DEC);
            // Serial.println(";");
        }
    }

    if(millis() - md25_update_time > md25_delay_update){
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
        md25_update_time = millis();
    }

}