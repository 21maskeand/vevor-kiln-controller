/**
 * @file buttons.h
 * @brief This file contains the code for pressing a specific button on the vevor kiln.
 */

#pragma once

/**
 * @brief This function will press the button at servo_id.
 *
 * @param servo_id The servo / button to press.
 * @param press_length The ammount of time to press the button for.
 */
void press_Button(int servo_id , int press_length);

