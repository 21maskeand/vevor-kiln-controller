#include "sd_control.h"
#include "config.h"
#include <SDFat.h>
#include <Arduino.h>

SDFat sd;
bool card_detected = false;

void sd_Control_Init()
{
  pinMode(CD_PIN , INPUT_PULLUP);

}

