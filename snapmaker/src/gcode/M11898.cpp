/*
Custom added Command to be able to send CANBus messages from GCode. 
I.E tell a supervisioning system a Print has started, The initcode has run, A print is finished.
No Input Validation will be made. You can Possible break your Printer if the wrong commands are sent. 

Parameters:
I = ID 
A = 1st byte
B = 2nd Byte
C = 3rd Byte
D = 4th Byte
E = 5th Byte
F = 6th Byte
G = 7th Byte
H = 8th Byte


*/
//Include bunch of stuff
#include "../common/debug.h"
#include "../common/config.h"
#include "../service/system.h"
#include "../module/can_host.h"

// marlin headers
#include  "src/gcode/gcode.h"

#if (MOTHERBOARD == BOARD_SNAPMAKER_2_0)

void GcodeSuite::M11898() {
CanStdMesgCmd_t cmd;
CanPacket_t  packet;

uint8_t         buffer[8];
cmd.length = 0;
int16_t maxID = 2047;
int address;

SERIAL_ECHOLN("CAN_Function Called");


  if(parser.seen('I')) {
    address = parser.value_int();
    SERIAL_ECHOLN("Adress to talk to" + address);
    if (address <= maxID){
      cmd.id = address;
      }
      else
      {
        SERIAL_ECHOLN("Adress bigger then 2047, select a lower one Please");
      }
      
  }

  if(parser.seen('A')) {
    buffer[0] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("A= "+parser.value_byte());
    }
    else
    {
      buffer[0] = 0;
    }
  if(parser.seen('B')) {

    buffer[1] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("B= "+parser.value_byte());
    }
    else
    {
      buffer[1] = 0;
    }
  if(parser.seen('C')) {
    buffer[2] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("C= "+parser.value_byte());
    }
    else
    {
      buffer[2] = 0;
    }
  if(parser.seen('D')) {
    buffer[3] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("D= "+parser.value_byte());
    }
    else
    {
      buffer[3] = 0;
    }
  if(parser.seen('E')) {
    buffer[4] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("E= "+parser.value_byte());
    }
    else
    {
      buffer[4] = 0;
    }
  if(parser.seen('F')) {
    buffer[5] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("F= "+parser.value_byte());
    }
    else
    {
      buffer[5] = 0;
    }
  if(parser.seen('G')) {
    buffer[6] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("G= "+parser.value_byte());
    }
    else
    {
      buffer[6] = 0;
    }
  if(parser.seen('H')) {
    buffer[7] = parser.value_byte();
    cmd.length +=1;
    SERIAL_ECHOLN("H= "+parser.value_byte());
    }
    else
    {
      buffer[7] = 0;
    }

  if(cmd.id <2048){
  cmd.data = buffer;
  //cmd.length = 8; //in theory not used as each of the command parts add to the lenght?  


  packet.ch = CAN_CH_2;//Hardcode to CAN2 as thats the one used for Modules
  packet.id = cmd.id;

  packet.ft     = CAN_FRAME_STD_DATA;
  packet.data   = cmd.data;
  packet.length = cmd.length;

 can.Write(packet);
  }

}






#endif // MOTHERBOARD == BOARD_SNAPMAKER_2_0