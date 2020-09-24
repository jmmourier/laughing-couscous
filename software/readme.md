# Software 

The software if the programm that is running on the main computer on the robot. 

## introduction

The software is organize around __modules__ for each business logic purpose
and __application__ for integration.

## modules 
hali : Hardware Abstraction Layer Interface   
gui : Graphical User Interface  
moti : Motion of the robot  
posi : Positioning of the robot  
missi : Mission of the robot  
planni : plannificator of the robot  

## external modules 

## build
to build the software

    mkdir build
    cd build 
    cmake ..
    make

## troubleshooting 
in order to build the project you need to install few libraries : 

    sudo apt-get install libboost-all-dev
    sudo apt-get install libssl-dev

