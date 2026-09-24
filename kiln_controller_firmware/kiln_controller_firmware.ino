#include "config.h"
#include "sd_control.h"
#include "buttons.h"
#include <ArduioJson.h>

enum Controller_Status {READY , ERROR , IN_PROGRESS};

bool sd_card_in = false;
Controller_Status status = READY;
int current_temp;

void setup() 
{
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
  if (status == READY) digitalWrite(READY_LED_PIN , HIGH);
  else if (status == ERROR) digitalWrite(ERROR_LED_PIN , HIGH);
  else if (status == IN_PROGRESS) digitalWrite(IN_PROGRESS_LED_PIN , HIGH);
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

int min_To_Millis(int time)
{
  return time * 60000;
}

void do_Stage(int temp , float ramp , int hold_time)
{
  int temp_diff = temp - current_temp;
  bool direction = temp_diff > 0;

  float change_time = get_Time();
  for (int i = 0; i < abs(temp_diff); i ++)
  {
    float minutes_per_degree = 1 / ramp;
    while (true)
    {
      if ((get_Time() - change_time) > minutes_per_degree)
      {
        change_time = get_Time();

        press_Button(U_ID , LONG_PRESS);
        if (direction) press_Button(UP_ID , SHORT_PRESS);
        else press_Button(DOWN_ID , SHORT_PRESS);
        press_Button(P_ID , LONG_PRESS);

        break;
      }
    }

    current_temp = temp;
    delay(min_To_Millis(hold_time));
    
  }

  current_temp = temp;
}

CONTROLLER_STATUS controller_go()
{
  int temps[MAX_STAGES];
  float ramps[MAX_STAGES];
  int hold_times[MAX_STAGES];
  int n_stages;

  JsonDocument doc;
  if (load_Doc(SCHEDULE_PATH , doc))
  {
    n_stages = load_Schedule(doc , temps , ramps , hold_times , MAX_STAGES);
    if (n_stages == -1) return ERROR;
    else
    {
      for (int i = 0; i < n_stages; i++)
      {
        if (temps[i] > MAX_TEMP) return ERROR;
      }
      for (int i = 0; i < n_stages; i++)
      {
        do_Stage(temps[i] , ramps[i] , hold_times[i]);
      }
      go_To_Zero();
      return READY;
    }

  }
  else return ERROR;
}

void loop() 
{
  led_Update();

  sd_card_in = is_Card();
  if (sd_card_in)
  {
    go_To_Zero();
    status = IN_PROGRESS;
    led_Update();
    status = controller_go();
    led_Update();

    while (true)
    {
      if (! is_Card())
      {
        break;
      }
    }
  }

}






