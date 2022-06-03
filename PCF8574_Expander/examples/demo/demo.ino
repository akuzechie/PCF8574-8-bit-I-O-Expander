//---------------------------------------------
// PCF8574 8-bit Expander as Input & as Output 
// using Library PCF8574_Expander.h
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------
#include <PCF8574_Expander.h>
//----------------------------
PCF8574_Expander PCF8574;           /*declare object*/
//======================================================================
void setup()
{
  PCF8574.Init_I2C();               /*initialize I2C*/
  PCF8574.sendByte(0x42, 0);        /*clear PCF8574 (add 0x42)*/
  delay(1000);
}
//======================================================================
void loop()
{
  byte data = PCF8574.getByte(0x41);/*get data from PCF8574 (add 0x41)*/
  PCF8574.sendByte(0x42, data);     /*send data to PCF8574 (add 0x42)*/
}