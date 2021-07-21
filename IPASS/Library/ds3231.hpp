#ifndef _DS3231_HPP
#define _DS3231_HPP

#include "hwlib.hpp"

#define address 0x68 //Chip address

#define regSeconds 0x00 
#define regMinutes 0x01
#define regHours 0x02
#define regDay 0x03
#define regDate 0x04
#define regMonth 0x05
#define regYear 0x06

int monthSize[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Amount of days of every month



/// \brief
///Library of the ds3231 rtc chip
/// \details
///This class lets you use functions to communicate with the ds3231 rtc chip
class ds3231{
private:
    hwlib::i2c_bus & i2c_Bus; //I2c bus. Used to write() and read().
    
    /// \brief
    ///Converts binary to decimals
    /// \details
    ///This functions converts a binary value to a decimal value and returns it.
    int BcdToDec(uint8_t bcd){ return (( bcd/16*10 ) + ( bcd%16 ) ); }
    
    /// \brief
    ///Converts decimals to binary
    /// \details
    ///This functions converts a decimal value to a binary value and returns it.
    uint8_t DecToBcd(int dec){ return (( dec/10*16 ) + ( dec%10 ) ); }

public: 
    /// \brief
    ///Makes object with the i2c bus
    /// \details 
    ///This constructor makes a object with the i2c bus. 
    ds3231( hwlib::i2c_bus_bit_banged_scl_sda & i2c_Bus):
    i2c_Bus(i2c_Bus)
    {}
    
    /// \brief 
    ///Sets the time
    /// \details
    /// This functions sets the time and date by calling all set functions and passing the right time.
    void setTime(int seconds, int minutes, int hours, int day, int date, int month, int year){
        setSeconds(seconds);
        setMinutes(minutes);
        setHours(hours);
        setDay(day);
        setDate(date);
        setMonth(month);
        setYear(year);
    }

    /// \brief
    /// Returns the time
    /// \details
    ///This functions returns the time and date by calling all get functions.
    void getTime(){
        getSeconds();
        getMinutes();
        getHours();
        getDay();
        getDate();
        getMonth();
        getYear();
    }
    
    /// \brief
    ///Returns the seconds
    /// \details 
    ///This functions returns the seconds. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the seconds from binary to decimals and it reads the seconds.
    int getSeconds(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regSeconds);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
    /// \brief
    ///Returns the minutes
    /// \details 
    ///This functions returns the minutes. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the minutes from binary to decimals and it reads the minutes.
    int getMinutes(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regMinutes);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }

    /// \brief
    ///Returns the hours
    /// \details 
    ///This functions returns the hours. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the hours from binary to decimals and it reads the hours.
    int getHours(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regHours);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }

    /// \brief
    ///Returns the day
    /// \details 
    ///This functions returns the day. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the day from binary to decimals and it reads the day.
    int getDay(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regDay);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }

    /// \brief
    ///Returns the date
    /// \details 
    ///This functions returns the date. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the date from binary to decimals and it reads the date.
    int getDate(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regDate);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }

    /// \brief
    ///Returns the month
    /// \details 
    ///This functions returns the month. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the month from binary to decimals and it reads the month.
    int getMonth(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regMonth);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }

    /// \brief
    ///Returns the year
    /// \details 
    ///This functions returns the year. First it writes to the right registry to point out the registry it wants to read from.
    ///Then it converts the value of the year from binary to decimals and it reads the year.
    int getYear(){
        {
            auto writeTo = i2c_Bus.write(address);
            writeTo.write(regYear);
        }

        return BcdToDec(i2c_Bus.read(address).read_byte());
    }
    
    /// \brief
    ///Sets the seconds
    /// \details 
    ///This functions sets the seconds in the seconds registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 59 it becomes 0. If it is smaller then 0 it becomes 59.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary. 
    void setSeconds(int seconds){
        if(seconds > 59){
            seconds = 0;
        }
        else if(seconds < 0){
            seconds = 59;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regSeconds);
        writeTo.write(DecToBcd(seconds));
    }
    
    /// \brief
    ///Sets the minutes
    /// \details 
    ///This functions sets the minutes in the minutes registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 59 it becomes 0. If it is smaller then 0 it becomes 59.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setMinutes(int minutes){
        if(minutes > 59){
            minutes = 0;
        }
        else if(minutes < 0){
            minutes = 59;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regMinutes);
        writeTo.write(DecToBcd(minutes));
    }

    /// \brief
    ///Sets the hours
    /// \details 
    ///This functions sets the hours in the hours registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 23 it becomes 0. If it is smaller then 0 it becomes 23.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setHours(int hours){
        if(hours > 23){
            hours = 0;
        }
        else if(hours < 0){
            hours = 23;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regHours);
        writeTo.write(DecToBcd(hours));
    }

    /// \brief
    ///Sets the day
    /// \details 
    ///This functions sets the day in the day registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 7 it becomes 1. If it is smaller then 1 it becomes 7.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setDay(int day){
        if(day > 7){
            day = 1;
        }
        else if(day < 1){
            day = 7;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regDay);
        writeTo.write(DecToBcd(day));
    }

    /// \brief
    ///Sets the date
    /// \details 
    ///This functions sets the date in the date registry. First it checks if the value that is givin is valid.
    ///If the value is greater than the amount of days in that month it becomes 1. If it is smaller then 1 it becomes the last day of that month.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setDate(int date){
        if(date > monthSize[getMonth() - 1]){
            date = 1;
        }
        else if(date < 1){
            date = monthSize[getMonth() - 1];
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regDate);
        writeTo.write(DecToBcd(date));
    }

    /// \brief
    ///Sets the month
    /// \details 
    ///This functions sets the month in the month registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 12 it becomes 1. If it is smaller then 1 it becomes 12.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setMonth(int month){
        if(month > 12){
            month = 1;
        }
        else if(month < 1){
            month = 12;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regMonth);
        writeTo.write(DecToBcd(month));
    }

    /// \brief
    ///Sets the year
    /// \details 
    ///This functions sets the year in the year registry. First it checks if the value that is givin is valid.
    ///If the value is greater than 99 it becomes 0. If it is smaller then 0 it becomes 99.
    ///After the check it writes to the right address, the right registry, the value converted from decimals to binary.
    void setYear(int year){
        if(year > 99){
            year = 0;
        }
        else if(year < 0){
            year = 99;
        }
        auto writeTo = i2c_Bus.write(address);
        writeTo.write(regYear);
        writeTo.write(DecToBcd(year));
    }

};

#endif
