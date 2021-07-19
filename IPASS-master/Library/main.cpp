#include "ds3231.hpp"

int main( void ){	   
   WDT->WDT_MR = WDT_MR_WDDIS;

   namespace target = hwlib::target;
   
   const char *states[6] = {"Minutes", "Hours", "Day", "Date", "Month", "Year"};
   const char *days[7]  = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
   int monthSize[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   auto i2c_Bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

   auto oled    = hwlib::glcd_oled( i2c_Bus, 0x3c ); 
   auto font    = hwlib::font_default_8x8();
   auto display = hwlib::terminal_from( oled, font );

   auto leftSw = target::pin_in_out( target::pins::d22 );
   auto oke = target::pin_in_out( target::pins::d33 );
   auto rightSw = target::pin_in_out( target::pins::d32 );

   ds3231 clock = (i2c_Bus);

   int state = 0;

   clock.setTime(0,59,23,7,18,7,21);
   
   for(;;){     
   display 
      << "\f" << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds()  
      << "\n" << days[clock.getDay() - 1]
      << "\t0404" << clock.getDate() << "-" << clock.getMonth() << "-" << (clock.getYear() + 2000) 
      << "\t0406" << states[state]
      << hwlib::flush; 

      if(!leftSw.read()){
         if(state <= 0){
            state = 5;
         }
         else{
            state -= 1;
         }
      }  
      else if(!oke.read()){
         hwlib::wait_ms(1000);
         while(true){
            if(state == 0){
               if(!rightSw.read()){
                  if(clock.getMinutes() >= 59){
                     clock.setMinutes(0);
                  }
                  else{
                     clock.setMinutes(clock.getMinutes() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getMinutes() <= 0){
                     clock.setMinutes(59);
                  }
                  else{
                     clock.setMinutes(clock.getMinutes() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 1){
               if(!rightSw.read()){
                  if(clock.getHours() >= 23){
                     clock.setHours(0);
                  }
                  else{
                     clock.setHours(clock.getHours() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getHours() <= 0){
                     clock.setHours(23);
                  }
                  else{
                     clock.setHours(clock.getHours() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 2){
               if(!rightSw.read()){
                  if(clock.getDay() >= 7){
                     clock.setDay(1);
                  }
                  else{
                     clock.setDay(clock.getDay() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getDay() <= 1){
                     clock.setDay(7);
                  }
                  else{
                     clock.setDay(clock.getDay() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 3){
               if(!rightSw.read()){
                  if(clock.getDate() >= monthSize[clock.getMonth()]){
                     clock.setDate(1);
                  }
                  else{
                     clock.setDate(clock.getDate() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getDate() <= 1){
                     clock.setDate(monthSize[clock.getMonth()]);
                  }
                  else{
                     clock.setDate(clock.getDate() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 4){
               if(!rightSw.read()){
                  if(clock.getMonth() >= 12){
                     clock.setMonth(1);
                  }
                  else{
                     clock.setMonth(clock.getMonth() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getMonth() <= 1){
                     clock.setMonth(12);
                  }
                  else{
                     clock.setMonth(clock.getMonth() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 5){
               if(!rightSw.read()){
                  if(clock.getYear() >= 99){
                     clock.setYear(0);
                  }
                  else{
                     clock.setYear(clock.getYear() + 1);
                  }
               }
               else if(!leftSw.read()){
                  if(clock.getYear() <= 0){
                     clock.setYear(99);
                  }
                  else{
                     clock.setYear(clock.getYear() - 1);
                  }
               }
               else if(!oke.read()){
                  break;
               }
            }
            
            display 
               << "\f" << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds()  
               << "\n" << days[clock.getDay() - 1]
               << "\t0404" << clock.getDate() << "-" << clock.getMonth() << "-" << (clock.getYear() + 2000) 
               << "\t0406" << states[state]
               << hwlib::flush;
         }
      }

      else if(!rightSw.read()){
         if(state >= 5){
            state = 0;
         }
         else{
            state += 1;
         }
      }  
   }  
}