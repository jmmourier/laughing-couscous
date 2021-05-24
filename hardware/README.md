# Hardware

Pin connections on pro micro : 

                  USB   
            ┌─────────────┐
    MD25 RX │TX        RAW│
    MD25 TX │RX        GND│
            │GND     RESET│
            │GND       VCC│
     I2C US │2-SDA      A3│
     I2C US │3-SCL      A2│
    Grabber │4          A1│
       Flag │5          A0│
            │6          15│
   Select 1 │7          14│Start button
            │8          16│Led R (HS)
   Select 3 │9          10│Led G
            └─────────────┘
