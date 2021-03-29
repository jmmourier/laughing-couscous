#include "MessageParser/MessageParser.cpp"

MessageParser message_parser_;
const int buffer_size = 80;
char buffer_[buffer_size];
int buffer_fullfillness = 0;

void setup() {
    Serial.begin(9600);
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);
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
        if(input_char == message_parser_.getEndChar()){
            CommandData command_data = message_parser_.parse(buffer_);
            memset(buffer_, 0, sizeof(buffer_));
            buffer_fullfillness = 0;

            Serial.print("parsed command id : ");
            Serial.print(command_data.command_);
            Serial.print(" argument : ");
            Serial.println(command_data.argument_,DEC);
        }
    }

}