#include "globals.h"
#include <DateTimeTZ.h>

float bpm = 0.0f, spo2 = 0.0f;

IPAddress local_IP(192, 168, 43, 99);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

const char *ssid = "SSID";
const char *password = "PASSWORD";

void setup_wifi(const char *ssid, const char *password) {
    Serial.printf("Connecting to %s\n", ssid);
    //  connect to local wi-fi network
    WiFi.begin(ssid, password);
    
    // check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
}

void setup_ntp() {
    DateTime.setServer("pool.ntp.org");
    DateTime.setTimeZone(TZ_America_Fortaleza);
    DateTime.begin();
    if (!DateTime.isTimeValid())
    {
        Serial.println("Failed to get time from server.");
    } else {
        Serial.println("Success to get time from server.\nCurrent Time:");
        Serial.println(DateTime.toISOString());
    }
}
