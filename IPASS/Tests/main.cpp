#include "../Library/ds3231.hpp"

int main( void ){	   
   WDT->WDT_MR = WDT_MR_WDDIS;

   namespace target = hwlib::target;

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   auto i2c_Bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

   ds3231 clock = (i2c_Bus);

   
   clock.setTime(55,59,23,1,31,12,21); //Sets the time (23:59:55 1 31-12-21)
   for(int i = 0; i < 6; i++){ //This confirms that the library works. (0:0:0 2 1-1-22)
      hwlib::cout << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds() << " " << clock.getDay() << " " << clock.getDate() << "-" << clock.getMonth() << "-" << clock.getYear() << '\n';
      hwlib::wait_ms(1000);
   }

   hwlib::cout << "----------------------------------------------------------------------------------" << '\n';
   clock.setTime(355,455,333,566,123,424,655); //Sets invalid inputs positive
   for(int i = 0; i < 6; i++){ //This confirms that the library works. (0:0:0 1 1-1-00)
      hwlib::cout << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds() << " " << clock.getDay() << " " << clock.getDate() << "-" << clock.getMonth() << "-" << clock.getYear() << '\n';
      hwlib::wait_ms(1000);
   }

   hwlib::cout << "----------------------------------------------------------------------------------" << '\n';
   clock.setTime(-1,-1,-1,-1,-1,-1,21); //Sets invalid inputs negative (23:59:59 7 31-12-21)
   for(int i = 0; i < 6; i++){ //This confirms that the library works. (0:0:0 1 1-1-22)
      hwlib::cout << clock.getHours() << ":" << clock.getMinutes() << ":" << clock.getSeconds() << " " << clock.getDay() << " " << clock.getDate() << "-" << clock.getMonth() << "-" << clock.getYear() << '\n';
      hwlib::wait_ms(1000);
   }

}