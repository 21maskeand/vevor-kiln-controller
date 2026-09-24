#include "sd_control.h"
#include "config.h"
#include <SdFat.h>
#include <ArduinoJson.h>
#include <Arduino.h>

SDFat sd;

void sd_Control_Init()
{
  pinMode(SD_CD_PIN , INPUT_PULLUP);

}

bool is_Card()
{
  if (digitalRead(SD_CD_PIN) == LOW)
  {
    delay(200);
    if (digitalRead(SD_CD_PIN) == LOW)
    {
      sd.begin();
      return true;
    }
  }
  return false;
}

bool load_Doc(const char* path , JsonDocument& doc)
{
  File f = sd.open(path , O_RDONLY);
  if (!f) return false;
  DeserializationError er = deserializeJson(doc , f);
  f.close();
  if (er)
  {
    return false;
  }
  else
  {
    return true;
  }

}

int read_Int_Array(JsonArrayConst arr , int* out , int max_count)
{
  if (arr.isNull()) return -1;
  int n = 0;
  for (JsonVariantConst v : arr)
  {
    if (n >= max_count) break;
    out[n++] = v.as<int>();
  }
  return n;
}

int read_Float_Array(JsonArrayConst arr , float* out , int max_count)
{
  if (arr.isNull()) return -1;
  int n = 0;
  for (JsonVariantConst v : arr)
  {
    if (n >= max_count) break;
    out[n++] = v.as<float>();
  }
  return n;
}

int read_Schedule(JsonDocument& doc , int* temps , float* ramps , int* hold_times , int max_count)
{
  n_temps = read_Int_Array(doc["temps"].as<JsonArrayConst>() , temps , max_count);
  n_ramps = read_Float_Array(doc["ramps"].as<JsonArrayConst>() , ramps , max_count);
  n_hold_times = read_Int_Array(doc["hold_times"].as<JsonArrayConst>() , hold_times , max_count);

  if ((n_temps > max_count) || (n_ramps > max_count) || (n_hold_times > max_count)) return -1;

  if (n_temps == -1 || n_ramps == -1 || n_times == -1) return -1;
  if ((n_temps != n_ramps) || (n_ramps != n_hold_times)) return -1;
  return n_temps;

}






