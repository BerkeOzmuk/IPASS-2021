#ifndef _DS3231_HPP
#define _DS3231_HPP

#include "hwlib.hpp"

int monthSize[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
    

    void setTime(int seconds, int minute, int hour, int day, int date, int month, int year){
        setSeconds(seconds);
        setMinutes(minute);
        setHours(hour);
        setDay(day);
        setDate(date);
        setMonth(month);
        setYear(year);
    }

    void getTime(){
        getSeconds();
        getMinutes();
        getHours();
        getDay();
        getDate();
        getMonth();
        getYear();
    }
    
    int getSeconds(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x00);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
     int getMinutes(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x01);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
     int getHours(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x02);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int getDay(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x03);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int getDate(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x04);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int getMonth(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x05);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int getYear(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x06);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
    void setSeconds(int seconds){
        if(seconds > 59){
            seconds = 0;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x00);
        writeTo.write(DecToBcd(seconds));
    }
    
    void setMinutes(int minutes){
        if(minutes > 59){
            minutes = 0;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x01);
        writeTo.write(DecToBcd(minutes));
    }

    void setHours(int hours){
        if(hours > 23){
            hours = 0;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x02);
        writeTo.write(DecToBcd(hours));
    }

    void setDay(int day){
        if(day > 6){
            day = 0;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x03);
        writeTo.write(DecToBcd(day));
    }

    void setDate(int date){
        if(date > monthSize[getMonth() - 1]){
            date = 1;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x04);
        writeTo.write(DecToBcd(date));
    }

    void setMonth(int month){
        if(month > 12){
            month = 1;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x05);
        writeTo.write(DecToBcd(month));
    }

    void setYear(int year){
        if(year > 99){
            year = 0;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x06);
        writeTo.write(DecToBcd(year));
    }

    void setPause(){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x00);
        writeTo.write(128);
    }

    void setResume(){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x00);
        writeTo.write(0);
    }

    
};

#endif