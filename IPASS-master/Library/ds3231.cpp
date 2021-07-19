#include "ds3231.hpp"

    void ds3231::setTime(int seconds, int minute, int hour, int day, int date, int month, int year){
        setSeconds(seconds);
        setMinutes(minute);
        setHours(hour);
        setDay(day);
        setDate(date);
        setMonth(month);
        setYear(year);
    }

    void ds3231::getTime(){
        getSeconds();
        getMinutes();
        getHours();
        getDay();
        getDate();
        getMonth();
        getYear();
    }
    
    int ds3231::getSeconds(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x00);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
     int ds3231::getMinutes(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x01);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
     int ds3231::getHours(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x02);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int ds3231::getDay(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x03);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int ds3231::getDate(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x04);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int ds3231::getMonth(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x05);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    int ds3231::getYear(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(0x06);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
    void ds3231::setSeconds(int seconds){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x00);
        writeTo.write(DecToBcd(seconds));
    }
    
    void ds3231::setMinutes(int minutes){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x01);
        writeTo.write(DecToBcd(minutes));
    }

    void ds3231::setHours(int hours){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x02);
        writeTo.write(DecToBcd(hours));
    }

    void ds3231::setDay(int day){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x03);
        writeTo.write(DecToBcd(day));
    }

    void ds3231::setDate(int date){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x04);
        writeTo.write(DecToBcd(date));
    }

    void ds3231::setMonth(int month){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x05);
        writeTo.write(DecToBcd(month));
    }

    void ds3231::setYear(int year){
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(0x06);
        writeTo.write(DecToBcd(year));
    }