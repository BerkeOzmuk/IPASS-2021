#include "../Library/ds3231.hpp"

int main( void ){	   
   WDT->WDT_MR = WDT_MR_WDDIS; //Kill the watch dog

   namespace target = hwlib::target;
   
   const char *states[6] = {"Minutes", "Hours", "Day", "Date", "Month", "Year"}; //Array with all the states the user can choose to change
   const char *days[7]  = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; //array of all the days

   auto scl = target::pin_oc( target::pins::scl ); //scl pin
   auto sda = target::pin_oc( target::pins::sda ); //sda pin
   auto i2c_Bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda); //i2c bus

   auto oled    = hwlib::glcd_oled( i2c_Bus, 0x3c ); 
   auto font    = hwlib::font_default_8x8();
   auto display = hwlib::terminal_from( oled, font );

   auto leftSw = target::pin_in_out( target::pins::d22 ); //Left switch
   auto oke = target::pin_in_out( target::pins::d33 ); //Oke switch
   auto rightSw = target::pin_in_out( target::pins::d32 ); //Right switch

   ds3231 clock = (i2c_Bus);

   int state = 0;

   clock.setTime(1,1,1,1,1,1,1); //sets the time

   for(;;){     
   display //Displays the time on the oled
      << "\f" << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds()  
      << "\n" << days[clock.getDay() - 1]
      << "\t0404" << clock.getDate() << "-" << clock.getMonth() << "-" << (clock.getYear() + 2000) 
      << "\t0406" << states[state]
      << hwlib::flush; 

      if(!leftSw.read()){ //Checks if the left switch is pressed
         if(state <= 0){ //Checks what states it is on  
            state = 5;
         }
         else{
            state -= 1;
         }
      }  
      else if(!oke.read()){ //Checks if the Oke switch is pressed
         hwlib::wait_ms(1000);
         while(true){
            if(state == 0){ //Checks what state it is on and changes the time if needed. This counts for all the states
               if(!rightSw.read()){
                  clock.setMinutes(clock.getMinutes() + 1);
               }
               else if(!leftSw.read()){
                  clock.setMinutes(clock.getMinutes() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 1){
               if(!rightSw.read()){
                  clock.setHours(clock.getHours() + 1);
               }
               else if(!leftSw.read()){
                  clock.setHours(clock.getHours() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 2){
               if(!rightSw.read()){
                  clock.setDay(clock.getDay() + 1);
               }
               else if(!leftSw.read()){
                  clock.setDay(clock.getDay() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 3){
               if(!rightSw.read()){
                  clock.setDate(clock.getDate() + 1);
               }
               else if(!leftSw.read()){
                  clock.setDate(clock.getDate() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 4){
               if(!rightSw.read()){
                  clock.setMonth(clock.getMonth() + 1);
               }
               else if(!leftSw.read()){
                  clock.setMonth(clock.getMonth() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            if(state == 5){
               if(!rightSw.read()){
                  clock.setYear(clock.getYear() + 1);
               }
               else if(!leftSw.read()){
                  clock.setYear(clock.getYear() - 1);
               }
               else if(!oke.read()){
                  break;
               }
            }
            
            display //Displays the time
               << "\f" << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds()  
               << "\n" << days[clock.getDay() - 1]
               << "\t0404" << clock.getDate() << "-" << clock.getMonth() << "-" << (clock.getYear() + 2000) 
               << "\t0406" << states[state]
               << hwlib::flush;
         }
      }

      else if(!rightSw.read()){ //The same as the left switch but with the right switch
         if(state >= 5){ 
            state = 0;
         }
         else{
            state += 1;
         }
      }  
   }  
}