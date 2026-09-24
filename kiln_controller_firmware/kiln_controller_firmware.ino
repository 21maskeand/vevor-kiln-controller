#include "config.h"
#include "sd_control.h"
#include "buttons.h"
#include <ArduinoJson.h>

enum Controller_Status {READY , ERROR , IN_PROGRESS};

Card_Status card_status = OUT;
Controller_Status controller_status = READY;
int current_temp;

int temps[MAX_STAGES];
float ramps[MAX_STAGES];
int hold_times[MAX_STAGES];
int n_stages;
JsonDocument doc;

void setup() 
{
  Serial.begin(9600);
  sd_Control_Init();
  buttons_Init();
  led_Init();

}

void led_Init()
{
  pinMode(READY_LED_PIN , OUTPUT);
  pinMode(ERROR_LED_PIN , OUTPUT);
  pinMode(IN_PROGRESS_LED_PIN , OUTPUT);
}

void led_Update()
{
  if (controller_status == READY)
  {
    digitalWrite(READY_LED_PIN , HIGH);
    digitalWrite(ERROR_LED_PIN , LOW);
    digitalWrite(IN_PROGRESS_LED_PIN , LOW);
  }
  else if (controller_status == ERROR) 
  {
    digitalWrite(READY_LED_PIN , LOW);
    digitalWrite(ERROR_LED_PIN , HIGH);
    digitalWrite(IN_PROGRESS_LED_PIN , LOW);
  }
  else if (controller_status == IN_PROGRESS) 
  {
    digitalWrite(READY_LED_PIN , LOW);
    digitalWrite(ERROR_LED_PIN , LOW);
    digitalWrite(IN_PROGRESS_LED_PIN , HIGH);
  }
}

void go_To_Zero()
{
  press_Button(U_ID , LONG_PRESS);
  press_Button(DOWN_ID , VERY_LONG_PRESS);
  press_Button(P_ID , LONG_PRESS);
  current_temp = 0;
}

float get_Time()
{
  return millis() / 60000.0;
}

unsigned long min_To_Millis(int time)
{
  return time * 60000;
}

float max_Ramp_For_Num_Presses(int num_presses)
{
  float minutes = (LONG_PRESS + WAIT_TIME + ((SHORT_PRESS + WAIT_TIME) * num_presses) + LONG_PRESS + WAIT_TIME) / 60000.0;
  return num_presses / minutes;
}

void do_Ramp_Section(float ramp , int num_presses , int increments , bool direction)
{
  float change_time = get_Time();
  for (int i = 0; i < increments; i ++)
  {
    float interval = num_presses / ramp;
    while (true)
    {
      card_status = is_Card_And_Mount_If();
      if (card_status != OUT)
      {
        return;
      }

      if ((get_Time() - change_time) > interval)
      {
        change_time = get_Time();
        press_Button(U_ID , LONG_PRESS);
        for (int press = 0; press < num_presses; press++)
        {
          if (direction) press_Button(UP_ID , SHORT_PRESS);
          else press_Button(DOWN_ID , SHORT_PRESS);
        }
        press_Button(P_ID , LONG_PRESS);

        break;
      }
    } 
  }
}

void do_Ramp(int temp , float ramp)
{
  int temp_diff = temp - current_temp;
  if (temp_diff == 0) return;
  bool direction = temp_diff > 0;

  int num_presses = 1;
  while (true)
  {
    if (max_Ramp_For_Num_Presses(num_presses) > ramp) break;
    else num_presses++;
  }

  if (card_status == OUT) do_Ramp_Section(ramp , num_presses , abs(temp_diff) / num_presses , direction);
  if ((card_status == OUT) && (abs(temp_diff) % num_presses)) do_Ramp_Section(ramp , abs(temp_diff) % num_presses , 1 , direction);

}

void do_Stage(int temp , float ramp , int hold_time)
{
  do_Ramp(temp , ramp);
  if (card_status != OUT) return;
  current_temp = temp;
  unsigned long start_time = millis();
  while (millis() - start_time < min_To_Millis(hold_time))
  {
    card_status = is_Card_And_Mount_If();
    if (card_status != OUT)
    {
      return;
    }
  }

  current_temp = temp;

}

Controller_Status controller_Start()
{
  if (load_Doc(SCHEDULE_PATH , doc))
  {
    n_stages = load_Schedule(doc , temps , ramps , hold_times , MAX_STAGES);
    if (n_stages == -1) return ERROR;
    else
    {
      float max_ramp = max_Ramp_For_Num_Presses(MAX_RAMP_PRESSES_CHECK);
      for (int i = 0; i < n_stages; i++)
      {
        if (temps[i] > MAX_TEMP) {Serial.print(F("Temp ")); Serial.print(i); Serial.print(F(" of ")); Serial.print(temps[i]); Serial.println(F(" exceeds the maximum set.")); return ERROR;}
        if (temps[i] < 0) {Serial.print(F("Temp ")); Serial.print(i); Serial.print(F(" of ")); Serial.print(temps[i]); Serial.println(F(" cannot be less than zero.")); return ERROR;}
        if (ramps[i] <= 0) {Serial.print(F("Ramp ")); Serial.print(i); Serial.print(F(" of ")); Serial.print(ramps[i]); Serial.println(F(" cannot be less than or equal to zero.")); return ERROR;}
        if (ramps[i] > max_ramp) {Serial.print(F("Ramp ")); Serial.print(i); Serial.print(F(" of ")); Serial.print(ramps[i]); Serial.print(F(" exceeds the maximum ramp speed for this configuration of ")); Serial.println(max_ramp); return ERROR;}
        if (hold_times[i] < 0) {Serial.print(F("Hold time ")); Serial.print(i); Serial.print(F(" of ")); Serial.print(hold_times[i]); Serial.println(F(" Cannot be less than zero.")); return ERROR;}
        
      }
      return READY;
    }

  }
  else return ERROR;
}

Controller_Status controller_Go()
{
  for (int i = 0; i < n_stages; i++)
  {
    if (card_status == OUT) do_Stage(temps[i] , ramps[i] , hold_times[i]);
  }
  if (card_status != OUT)
  {
    Serial.println(F("SD card cannot be inserted while the schedule is running."));
    go_To_Zero();
    return ERROR;
  }
  else
  {
    go_To_Zero();
    return READY;
  }

}

void wait_Till_Card_Gone()
{
  Serial.println(F("Remove SD Card."));
  while (true)
  {
    card_status = is_Card_And_Mount_If();
    if (card_status == OUT) break;
  }
}

void loop() 
{
  led_Update();

  card_status = is_Card_And_Mount_If();
  if (card_status == GOOD)
  {
    
    controller_status = IN_PROGRESS;
    led_Update();

    controller_status = controller_Start();
    led_Update();
    if (controller_status == ERROR)
    {
      wait_Till_Card_Gone();
      return;
    }

    wait_Till_Card_Gone();

    controller_status = IN_PROGRESS;
    led_Update();
    go_To_Zero();

    controller_status = controller_Go();
    led_Update();
    if (controller_status == ERROR)
    {
      wait_Till_Card_Gone();
      return;
    }
  }
  else if (card_status == MOUNT_ERROR) wait_Till_Card_Gone();
}






