;---------------
; Assembly Code
;---------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"
;------------------------
.global I2C_init
.global I2C_start
.global I2C_write
.global I2C_read_NACK
.global I2C_stop
;==============================================================
I2C_init:
    LDI   R21, 0
    STS   TWSR, R21       ;prescaler = 0
    LDI   R21, 72
    STS   TWBR, R21       ;SCK freq = 100kHz
    LDI   R21, (1<<TWEN)
    STS   TWCR, R21       ;enable TWI
    RET
;==============================================================
I2C_start:
    LDI   R21, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
    STS   TWCR, R21       ;transmit START condition
    ;----------------------------------------------------------
wt1:LDS   R21, TWCR
    SBRS  R21, TWINT      ;TWI interrupt = 1?
    RJMP  wt1             ;no, wait for end of transmission
    ;----------------------------------------------------------
    RET
;==============================================================
I2C_write:
    STS   TWDR, R24       ;copy SLA+W into data register
    LDI   R21, (1<<TWINT)|(1<<TWEN)
    STS   TWCR, R21       ;transmit SLA+W
    ;----------------------------------------------------------
wt2:LDS   R21, TWCR
    SBRS  R21, TWINT
    RJMP  wt2             ;wait for end of transmission
    ;----------------------------------------------------------
    RET
;==============================================================
I2C_read_NACK:
    LDI   R21, (1<<TWINT)|(1<<TWEN)
    STS   TWCR, R21         ;enable TWI & ACK
    ;----------------------------------------------------------
wt4:LDS   R21, TWCR
    SBRS  R21, TWINT
    RJMP  wt4               ;wait for data byte to be read
    ;----------------------------------------------------------
    LDS   R27, TWDR         ;store received byte
    RET
;==============================================================
I2C_stop:
    LDI   R21, (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)
    STS   TWCR, R21       ;transmit STOP condition
    RET