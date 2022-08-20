#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <WiFi.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ESPDateTime.h>
#include <ArduinoJson.h>

#define REPORTING_PERIOD_MS 1000

void setup_wifi(const char *ssid, const char *password);
void setup_ntp();

extern const char *ssid;
extern const char *password;

extern float bpm, spo2;

// Set static IP address
extern IPAddress local_IP;
// Set your Gateway IP address
extern IPAddress gateway;
extern IPAddress subnet;

#endif