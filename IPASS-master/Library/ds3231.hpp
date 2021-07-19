#ifndef _DS3231_HPP
#define _DS3231_HPP

#include "hwlib.hpp"

class ds3231{
private:
    hwlib::i2c_bus & i2c_Bus;
    uint8_t address = 0x68;

    int BcdToDec(uint8_t bcd){ return (( bcd/16*10 ) + ( bcd%16 ) ); }
    
    uint8_t DecToBcd(int dec){ return (( dec/10*16 ) + ( dec%10 ) ); }

public: 
    ds3231( hwlib::i2c_bus_bit_banged_scl_sda & i2c_Bus):
    i2c_Bus(i2c_Bus)
    {}
    

    void getTime();
    void setTime(int second, int minute, int hour, int day, int date, int month, int year);    
    
    int getSeconds();
    int getMinutes();
    int getHours();
    int getDay();
    int getDate();
    int getMonth();
    int getYear();

    void setSeconds(int second);
    void setMinutes(int minute);
    void setHours(int hour);
    void setDay(int day);
    void setDate(int date);
    void setMonth(int month);
    void setYear(int year);
 
};

#endif