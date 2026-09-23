/**
 * @file servo.h
 * @brief This file contains the code for moving the servos.
 */

#pragma once

/**
 * @brief Initialize the servo driver and set frequencies.
 */
void servos_Init();

/**
 * @brief Sends the servo at servo_id to a given angle.
 *
 * @param servo_id The id of the servo to move.
 * @param angle The angle to move the servo to.
 */
void servo_Go_To_Angle(int servo_di , float angle);