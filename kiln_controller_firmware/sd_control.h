/**
 * @file sd_control.h
 * @brief This file contains the code for sd card 
 */

#pragma once
#include <ArduinoJson.h>

/**
 * @brief Initializies sd control.
 */
void sd_Control_Init();

/**
 * @brief Checks if an SD card is still in after having been inserted.
 */
bool is_Card_Still_In();

/**
 * @brief Checks if an SD card has been inserted and mounts it if it has been.
 */
bool is_Card_And_Mount_If();

/**
 * @brief Loads a JsonDocument into doc.
 *
 * @param path The path to load from.
 * @param doc A JsonDocument to load into.
 */
bool load_Doc(const char* path , JsonDocument& doc);

/**
 * @brief Reads an int array from the json doc.
 *
 * @param arr The json array to load.
 * @param out The array to load into.
 * @param max_count The maximum number of values to read into out.
 */
int read_Int_Array(JsonArrayConst arr , int* out , int max_count);

/**
 * @brief Reads a float array from the json doc.
 *
 * @param arr The json array to load.
 * @param out The array to load into.
 * @param max_count The maximum number of values to read into out.
 */
int read_Float_Array(JsonArrayConst arr , float* out , int max_count);

/**
 * @brief Reads the entire schedule into given arrays
 *
 * @param doc The json doc to load from.
 * @param temps The temps array to load temps into.
 * @param ramps The ramps array to load ramps into.
 * @param times The times array to load times into.
 * @param max_count The maximum number of values to read into out.
 */
int load_Schedule(JsonDocument& doc , int* temps , float* ramps , int* times , int max_count);






