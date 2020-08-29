/****************************************************************
*                    Arduino MD25 test                          *
*****************************************************************/

// Values of 0 being sent using serial.write() have to be cast as a byte to stop them being misinterpereted as NULL
// This is a bug with arduino 1
#define CMD                 (byte)0x00              //  MD25 command byte of 0

#define WRITESP1            0x31                    // Byte writes speed to motor 1
#define WRITEACCEL          0x33                    // Byte writes a value of acceleration
#define RESETREG            0x35                    // Byte resets encoders
#define SETMODE             0x34                    // Byte sets mode
#define READIVS             0x2C                    // Byte reads motor currents and battery voltage        
#define READENCS            0x25                    // Byte reads both encoders
#define GET_VER             0x29

long encValue = 0;
byte softwareRev = 0;

void setup(){
  Serial1.begin(38400);
  Serial.begin(9600);
  
  Serial1.write(CMD);                                            // Set MD25 accelleration value
  Serial1.write(WRITEACCEL);
  Serial1.write(10);
  delayMicroseconds(10);                                        // Wait for this to be processed
  Serial1.write(CMD);                                            // Reset the encoder registers to 0
  Serial1.write(RESETREG);         
  Serial1.write(CMD);                                            // Set mode to 2, Both motors controlled by writing to speed 1
  Serial1.write(SETMODE);
  Serial1.write(2);    
  
  Serial1.write(CMD);                                            // Get software version of MD25
  Serial1.write(GET_VER);
  while(Serial1.available() < 1){}                               // Wait for byte to become available         
  softwareRev = Serial1.read();  
  
}

void loop(){ 
  while(encValue < 3000){               // While encoder 1 value less than 3000 move forward
    Serial1.write(CMD);                  // Set motors to drive forward at full speed
    Serial1.write(WRITESP1);
    Serial1.write(150);
    encValue = readEncoder();
    readVolts();
  }
  delay(100);
  while(encValue > 100){
    Serial1.write(CMD);                  // Drive motors reverse at full speed
    Serial1.write(WRITESP1);
    Serial1.write(100);
    encValue = readEncoder();
    readVolts();
  }
  delay(100);
}

long readEncoder(){                        // Function to read and display the value of both encoders, returns value of first encoder
  long result1 = 0; 
  long result2 = 0;
  Serial1.write(CMD);
  Serial1.write(READENCS);
  while(Serial1.available() < 8){}          // Wait for 8 bytes, first 4 encoder 1 values second 4 encoder 2 values 
  result1 = Serial1.read();                 // First byte for encoder 1, HH.
  result1 <<= 8;
  result1 += Serial1.read();                // Second byte for encoder 1, HL
  result1 <<= 8;
  result1 += Serial1.read();                // Third byte for encoder 1, LH
  result1 <<= 8;
  result1  += Serial1.read();               // Fourth byte for encoder 1, LL
  result2 = Serial1.read();
  result2 <<= 8;
  result2 += Serial1.read();
  result2 <<= 8;
  result2 += Serial1.read();
  result2 <<= 8;
  result2 += Serial1.read();

  
  Serial.print("Encoder 1:");               
  Serial.print(result1,DEC);
  Serial.println(";"); 
 
  Serial.print("Encoder 2:");
  Serial.print(result2,DEC);
  Serial.println(";");

  return result1;                                   
}
  
void readVolts(){                                                 // Function reads current for both motors and battery voltage
  byte batteryVolts, mot1_current, mot2_current = 0;
  Serial1.write(CMD);
  Serial1.write(READIVS);                                          // Send byte to readbattery voltage and motor currents
  while(Serial1.available() < 3){}                                 // Wait for the 3 bytes to become available then get them
  batteryVolts = Serial1.read();
  mot1_current = Serial1.read();
  mot2_current = Serial1.read();

  Serial.print("Mot1 I:");
  Serial.print(mot1_current,DEC);
  Serial.println(";")

  Serial.print("Mot2 I:");
  Serial.print(mot2_current,DEC);
  Serial.println(";"); 
  
  Serial.print("Rev:");
  Serial.print(softwareRev, DEC);
  Serial.println(";");
  
  Serial.print("Volts:");
  Serial.print(batteryVolts/10,DEC);                               // Seperate whole number and descimal place of battery voltage and display
  Serial.print(".");  
  Serial.print(batteryVolts%10,DEC);
  Serial.print(";");   
}
