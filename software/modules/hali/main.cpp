#include <iostream>

#include "Serial.h"
#include "MessageParser.h"

int serialReaderByLine(){
    try {

        Serial serial("/dev/ttyACM0",9600);

        serial.writeString("Hello world\n");
        while(true){
        std::cout<<serial.readLine()<<std::endl;
        }

    } catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }
}

int serialReaderByChar(){

    try {

        Serial serial("/dev/ttyACM0",9600);

        while(true){
        std::cout<<serial.readChar();
        }

    } catch(boost::system::system_error& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }
}

int testParser(){
    MessageParser myParser;
    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer('c');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('c');
    myParser.addCharToBuffer(';');
    
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('c');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(';');
    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(';');

    myParser.addCharToBuffer('a');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer(':');
    myParser.addCharToBuffer('b');
    myParser.addCharToBuffer(';');

    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    myParser.printBuffer();
    myParser.analyseBuffer().print();
    return 0;
}

int main(int argc, char* argv[])
{
   return testParser();
}

