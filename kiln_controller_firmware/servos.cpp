#include "servos.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = AdafuitPWMServoDriver(servo_driver_address);

/**
 * @brief Initialize the servo driver and set frequencies.
 */
void servos_Init()
{
  pwm.begin();
  pwm.setOscillatorFrequency(oscillator_freq);
  pwm.setPWMFreq(pwm_freq);

}

/**
 * @brief Sends the servo at servo_id to a given angle.
 *
 * @param servo_id The id of the servo to move.
 * @param angle The angle to move the servo to.
 */
void servo_Go_To_Angle(int servo_id , float angle)
{
  if (angle <= 0 || angle >= 180) {return;}
  float angle_frac = angle / 180;
  int microseconds = static_cast<int>((angle_frac * 1000) + 1000);
  pwm.writeMicroseconds(servo_channels[servo_id]);

}