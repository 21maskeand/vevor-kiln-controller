#include "servos.h"
#include "config.h"
#include <Wire.h>
#include <AdafruitPWMServoDriver.h>

AdafruitPWMServoDriver pwm = AdafuitPWMServoDriver(SERVO_DRIVER_ADDR);

void servos_Init()
{
  pwm.begin();
  pwm.setOscillatorFrequency(OSC_FREQ);
  pwm.setPWMFreq(PWM_FREQ);

}

void servo_Go_To_Angle(int servo_id , float angle)
{
  if (angle < 0 || angle > 180) {return;}
  float angle_frac = angle / 180;
  int microseconds = static_cast<int>((angle_frac * 1000) + 1000);
  pwm.writeMicroseconds(SERVO_CHANNELS[servo_id] , microseconds);

}