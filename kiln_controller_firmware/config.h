/**
 * @file config.h
 * @brief This file contains configuration values for use in the ret of the code.
 */

#pragma once
#include <stdint.h>

/**
 * @name Servo Configs
 * @brief These are the servo config variables.
 */
constexpr int SERVO_DRIVER_ADDR = 0x40;
constexpr uint32_t OSC_FREQ = 25000000;
constexpr int PWM_FREQ = 50;
constexpr int NUM_SERVOS = 4;
constexpr int SERVO_CHANNELS[NUM_SERVOS] = {0 , 1 , 2 , 3};
constexpr float SERVO_UNPRESS_ANGLE[NUM_SERVOS] = {0 , 0 , 0 , 0};
constexpr float SERVO_PRESS_ANGLE[NUM_SERVOS] = {30 , 30 , 30 , 30};
constexpr int SERVO_BOTTOM_ENDPOINT = 500;
constexpr int SERVO_TOP_ENDPOINT = 2500;

/**
 * @name Button Configs
 * @brief These are the button config variables
 */
constexpr int U_ID = 0;
constexpr int P_ID = 1;
constexpr int UP_ID = 2;
constexpr int DOWN_ID = 3;
constexpr unsigned long SHORT_PRESS = 100;
constexpr unsigned long LONG_PRESS = 3000;
constexpr unsigned long VERY_LONG_PRESS = 50000;
constexpr unsigned long WAIT_TIME = 500;

/**
 * @name SD Card Configs
 * @brief These are the SD Card configs.
 */
/// The SD chip select pin.
constexpr int SD_CS_PIN = 10;
/// The SD card chip detected pin, detects when an sd card is inserted.
constexpr int SD_CD_PIN = 2;
/// The value to set the serial clock speed to.
constexpr int SD_SCK_MHZ_VALUE = 4;

/**
 * @name Schedule Configs
 * @brief Contains all configs related to the schedule. 
 */
constexpr char SCHEDULE_PATH[] = "schedule.json";
constexpr int MAX_TEMP = 1200;
constexpr int MAX_STAGES = 15;
constexpr unsigned long MAX_RAMP_PRESSES_CHECK = 10000;

/**
 * @name Status Configs
 * @brief These are the configs for status LEDs
 */
constexpr int READY_LED_PIN = 13;
constexpr int ERROR_LED_PIN = 4;
constexpr int IN_PROGRESS_LED_PIN = 5;






