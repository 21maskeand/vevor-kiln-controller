#include "buttons.h"
#include "servos.h"
#include "config.h"

void buttons_Init()
{
  servos_Init();

}

void press_Button(int servo_id , int press_length)
{
  servo_Go_To_Angle(servo_id , SERVO_PRESS_ANGLE[servo_id]);
  delay(press_length);
  servo_Go_To_Angle(servo_id , SERVO_UNPRESS_ANGLE[servo_id]);
  delay(WAIT_TIME);
  
}