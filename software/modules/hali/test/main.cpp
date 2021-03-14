#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

#include "HalReal.h"
#include "HalSimu.h"
#include "IHali.h"

// #include "../src/Serial.h"
// #include "../src/MessageParser.h"

// int serialReaderByLine(){
//     try {

//         Serial serial("/dev/ttyACM0",9600);

//         serial.writeString("Hello world\n");
//         while(true){
//         std::cout<<serial.readLine()<<std::endl;
//         }

//     } catch(boost::system::system_error& e)
//     {
//         std::cout<<"Error: "<<e.what()<<std::endl;
//         return 1;
//     }
// }

// int serialReaderByChar(){

//     try {

//         Serial serial("/dev/ttyACM0",9600);

//         while(true){
//         std::cout<<serial.readChar();
//         }

//     } catch(boost::system::system_error& e)
//     {
//         std::cout<<"Error: "<<e.what()<<std::endl;
//         return 1;
//     }
// }

// int testParser(){
//     MessageParser myParser;
//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer('c');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('c');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('c');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(';');
//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(';');

//     myParser.addCharToBuffer('a');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer(':');
//     myParser.addCharToBuffer('b');
//     myParser.addCharToBuffer(';');

//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     myParser.printBuffer();
//     myParser.analyseBuffer().print();
//     return 0;
// }

// int testParseSerial(){

//     MessageParser myParser;
//     Serial serial("/dev/ttyACM0",9600);
//     while(true){
//         try
//         {
//     myParser.addCharToBuffer(serial.readChar());
//     CommandData command_data = myParser.analyseBuffer();
//     std::cout << command_data << std::endl;
//         }
//         catch(boost::system::system_error& e)
//         {
//             //std::cout<<"Error: "<<e.what()<<std::endl;
//         }
//     }
//     return 0;
// }

int main(int argc, char *argv[]) {
    try {
        IHali *hali;
        if (argc > 1) {
            if (std::string(argv[1]) == "-r") {
                auto realhali = new HalReal();
                hali = realhali;
            } else {
                auto realhali = new HalSimu();
                hali = realhali;
            }
        } else {
            auto realhali = new HalSimu();
            hali = realhali;
        }

        std::thread updater_thread(&IHali::updater, hali);
        std::chrono::milliseconds timespan(500);  // or whatever
        bool further = true;
        while (true) {
            std::cout << "md25 voltage  : " << hali->getBatteryVoltage() << std::endl;
            std::cout << "md25 encoder1 : " << hali->getEncoder(MotorIdEnum::motor1) << std::endl;
            std::cout << "md25 encoder2 : " << hali->getEncoder(MotorIdEnum::motor2) << std::endl;

            if (further) {
                if (hali->getEncoder(motor1) < 1000) {
                    hali->setMd25Speed(127 + 30, 127 + 30);
                    hali->setGrabber(grabberOpen);
                } else {
                    further = false;
                }
            } else {
                if (hali->getEncoder(motor1) > 0) {
                    hali->setMd25Speed(127 - 30, 127 - 30);
                    hali->setGrabber(grabberClose);
                } else {
                    further = true;
                }
            }

            std::this_thread::sleep_for(timespan);
        }
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}
