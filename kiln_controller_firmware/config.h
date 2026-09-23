/**
 * @file config.h
 * @brief This file contains configuration values for use in the ret of the code.
 */

#pragma once

/**
 * @name Servo Configs
 * @brief These are the servo config variables.
 */
constexpr int SERVO_DRIVER_ADDR = 0x40;
constexpr int OSC_FREQ = 25000000;
constexpr int PWM_FREQ = 50;
constexpr int SERVO_CHANNELS[4] = {0 , 1 , 2 , 3};
constexpr float SERVO_UNPRESS_ANGLE[4] = {0 , 0 , 0 , 0};
constexpr float SERVO_UNPRESS_ANGLE[4] = {30 , 30 , 30 , 30};

/**
 * @name Button Configs
 * @brief These are the button config variables
 */
constexpr int U_ID = 0;
constexpr int P_ID = 1;
constexpr int UP_ID = 2;
constexpr int DOWN_ID = 3;
constexpr int SHORT_PRESS = 100;
constexpr int LONG_PRESS = 3000;
constexpr int VERY_LONG_PRESS = 50000;
constexpr int WAIT_TIME = 1000;

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
constexpr str SCHEDULE_NAME = "schedule.json";
constexpr int MAX_TEMP = 1200;
