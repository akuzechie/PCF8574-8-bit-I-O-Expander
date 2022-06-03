//---------------------------------------------------
// PCF8574_Expander.cpp - Source File
// Library for Programming PCF8574 8-bit IO Expander
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------------
#include <Arduino.h>
#include <PCF8574_Expander.h>
//========================================================================
// Function prototypes, definition written in assembly
//========================================================================
extern "C"
{
  void I2C_init();
  void I2C_start();
  void I2C_write(byte);
  void I2C_read_NACK();
  void I2C_stop();
}
//========================================================================
// Constructor
//========================================================================
PCF8574_Expander::PCF8574_Expander() {}
//========================================================================
// Public Methods
//========================================================================
void PCF8574_Expander::Init_I2C()
{
  I2C_init();
}
//========================================================================
byte PCF8574_Expander::getByte(byte address)
{
  I2C_start();                /*send START condition*/
  I2C_write(address);         /*send read address of PCF8574*/
  I2C_read_NACK();            /*read data byte & send NACK*/
  I2C_stop();                 /*send STOP condition*/
  return TWDR;                /*return data byte stored in TWDR*/
}
//========================================================================
void PCF8574_Expander::sendByte(byte address, byte data)
{
  I2C_start();                /*send START condition*/
  I2C_write(address);         /*send write address of PCF8574*/
  I2C_write(~data);           /*send data byte*/
  I2C_stop();                 /*send STOP condition*/
}