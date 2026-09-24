#include "servos.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(SERVO_DRIVER_ADDR);

void servos_Init()
{
  pwm.begin();
  pwm.setOscillatorFrequency(OSC_FREQ);
  pwm.setPWMFreq(PWM_FREQ);
  
  for (int i = 0; i < NUM_SERVOS; i++)
  {
    servo_Go_To_Angle(i , SERVO_UNPRESS_ANGLE[i])
  }

}

void servo_Go_To_Angle(int servo_id , float angle)
{
  if (angle < 0 || angle > 180) {return;}
  float angle_frac = angle / 180;
  int microseconds = static_cast<int>((angle_frac * (SERVO_TOP_ENDPOINT - SERVO_BOTTOM_ENDPOINT)) + SERVO_BOTTOM_ENDPOINT);
  pwm.writeMicroseconds(SERVO_CHANNELS[servo_id] , microseconds);

}