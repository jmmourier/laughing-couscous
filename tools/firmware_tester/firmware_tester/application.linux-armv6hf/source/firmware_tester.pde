/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;
import java.util.Map;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
String serial_buffer = "";

boolean isSerialInError = false;

StringDict inventory;

void setup() 
{
  size(400, 400);
  
  String portName = Serial.list()[0];
  try{
  myPort = new Serial(this, portName, 9600);
  }
  catch(Exception e){
    background(0);
    textSize(32);
    text("No serial connected", 10, 30); 
    fill(0, 102, 153);
    isSerialInError = true;
  }
  
  inventory = new StringDict();

}

void draw()
{
  
  if(isSerialInError) return;
  
  background(0);
  
  // process serial
  readSerial();
  parseSerial();
  updateUI();
}

void readSerial(){
while ( myPort.available() > 0) {  // If data is available,
    char in_buffer = myPort.readChar(); 
    if(in_buffer != '\r' && 
      in_buffer != '\n'){
        serial_buffer += in_buffer;  
      }  
  }  
}

void parseSerial(){
  int positionEndFrame = serial_buffer.indexOf(";");
  if(serial_buffer.indexOf(";") == -1){
    return;
  }
  int positionParam = serial_buffer.indexOf(":");
  if(positionParam < positionEndFrame &&
    positionParam != -1) {
    String command = serial_buffer.substring(0,positionParam);
    String param = serial_buffer.substring(positionParam + 1,positionEndFrame);
    
    //print("command : " + command + " param : " + param);
    inventory.set(command,param);//updateInventory(command,param);
  }
  serial_buffer = serial_buffer.substring(positionEndFrame+1);
  //print("buffer : " + serial_buffer);
}


void updateUI(){
  
  textSize(32);
  fill(0, 102, 153);
  String[] theKeys = inventory.keyArray();
  for(int i = 0; i < theKeys.length; i++){
    text(theKeys[i] + " : " + inventory.get(theKeys[i]), 10, 30 * (i+1));
  }
}

  
