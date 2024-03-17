#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <memory>
#include <udevpp.hpp>
#include <thread>
#include <chrono>
#include <math.h>
#include <unistd.h>
#include <sysfspwm.hpp>




int main(int argc, char **argv)
{

  const int period_in_ns=20000000;
  const int servo_center= 1500000;
  const int servo_90P=     500000;
  const int servo_90N=    2500000;
  const int cycle_count = 4;
  const int servo_count = 4;
  const int cycles[cycle_count]= {servo_90P, servo_center, servo_90N,servo_center};

  sysfspwm::PWMChip mypwmchip("/sys/class/pwm/pwmchip6");

/*
  static sysfspwm::PWM servos[4]= {
     mypwmchip.export_pwm(0),
     mypwmchip.export_pwm(1),
     mypwmchip.export_pwm(2),
     mypwmchip.export_pwm(3)};
*/

  std::vector<sysfspwm::PWM> servos;

  for(int loop=0;loop<servo_count;loop++)
    {
     servos.push_back(mypwmchip.export_pwm(loop));
     servos[loop].set_period(std::chrono::nanoseconds(period_in_ns));
     servos[loop].set_duty_cycle(std::chrono::nanoseconds(servo_center));
     servos[loop].set_enabled(true);
    }

  //ok let's do something
  for(int cycle=0;cycle<cycle_count;cycle++)
     for(int servo=0;servo<servo_count;servo++)
       {
         servos[servo].set_duty_cycle(std::chrono::nanoseconds(cycles[cycle]));
         usleep(200000);
       }

  //All together do something
  for(int cycle=0;cycle<cycle_count;cycle++)
  {
     for(int servo=0;servo<servo_count;servo++)
         servos[servo].set_duty_cycle(std::chrono::nanoseconds(cycles[cycle]));
    usleep(200000);
  }

// disable
//     for(int servo=0;servo<servo_count;servo++)
//         servos[servo].set_enabled(false);


  return 0;

}
