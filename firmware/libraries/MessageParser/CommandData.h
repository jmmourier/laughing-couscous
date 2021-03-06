#ifndef COMMAND_DATA_H
#define COMMAND_DATA_H

enum CommandsEnum{
    speedMotor1,
    speedMotor2,
    versionRevisionRequested,
    grabberPositionRequested,
    resetEncoder,
    //reserved2,
    //reserved3,
    CommandsEnumMax
};

struct CommandsMessage{
    char* Messages_[CommandsEnumMax];
    CommandsMessage(){
        for (size_t i = 0; i < CommandsEnumMax; i++)
        {
            Messages_[i] = "";
        }
        Messages_[speedMotor1] = "md25speed1";
        Messages_[speedMotor2] = "md25speed2";
        Messages_[versionRevisionRequested] = "version";
        Messages_[grabberPositionRequested] = "grabber";
        Messages_[resetEncoder] = "resetEncoder";
    }
};

struct CommandData
{
    CommandData(CommandsEnum command, int argument) : 
        command_(command), argument_(argument){};
    CommandsEnum command_;
    int argument_;
};

#endif // COMMAND_DATA_H