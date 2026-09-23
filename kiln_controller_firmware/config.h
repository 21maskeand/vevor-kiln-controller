/**
 * @file config.h
 * @brief This file contains configuration values for use in the ret of the code.
 */

#pragma once

/**
 * @name Servo Configs
 * @brief These are the servo config variables.
 */
constexpr int servo_driver_address = 0x40;
constexpr int oscillator_freq = 25000000;
constexpr int pwm_freq = 50;
constexpr int servo_channels[4] = {0 , 1 , 2 , 3};
constexpr int servo_unpress_angle[4] = {0 , 0 , 0 , 0};
constexpr int servo_press_angle[4] = {30 , 30 , 30 , 30};

