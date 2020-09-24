# Firmware

## introduction
The firmware is running on arduino pro micro.  

## compile and deploy 
using the arduino cli tool :  

    ./arduino-cli compile --fqbn arduino:avr:leonardo myProject
    ./arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo myProject --log-level debug -v

more info on the [wiki](https://github.com/jmmourier/laughing-couscous/wiki/%5BTools%5D-Flashing-arduino)  