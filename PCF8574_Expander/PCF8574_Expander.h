//---------------------------------------------------
// PCF8574_Expander.h - Header File
// Library for Programming PCF8574 8-bit IO Expander
// by: Anas Kuzechie (June, 2022)
//---------------------------------------------------
//header guards
#ifndef PCF8574_Expander_h
#define PCF8574_Expander_h
//-----------------------------------------------------------
//class definition
class PCF8574_Expander
{
    public:
        //constructor
        PCF8574_Expander();
        //methods
        void Init_I2C();
        byte getByte(byte address);
        void sendByte(byte address, byte data);
};
//-----------------------------------------------------------
#endif