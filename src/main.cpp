#include "oximeter/globals.h"
#include "oximeter/webserver.h"
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <MAX30100_PulseOximeter.h>
#include <Wire.h>

const char *serverName = "https://oximeter-api.herokuapp.com/sensor/";

void blinkLED(uint32_t);
void collectDataFromSensor(void *);
void sendData(void *);
void blinkLEDInSensorRead(void *);

uint32_t tsLastReport = 0, tsLastDataSend = 0;
PulseOximeter pox;

DynamicJsonDocument request_body(2048);

void blinkLED(uint32_t milliseconds) {
  digitalWrite(BUILTIN_LED, HIGH);
  delay(milliseconds);
  digitalWrite(BUILTIN_LED, LOW);
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);

  setup_wifi(ssid, password);
  Serial.println("WiFi connected..!");
  Serial.printf("Got IP: %s\n", WiFi.localIP().toString());

  blinkLED(500);

  setup_ntp();

  if (MDNS.begin("oximetro")) {
    Serial.println("MDNS responder started");
  } else {
    Serial.println("Error starting mDNS");
    return;
  }

  setup_server();
  Serial.println("HTTP server started");

  MDNS.addService("http", "tcp", 80);

  Serial.println("Initializing pulse oximeter...");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;)
      ;
  } else {
    Serial.println("SUCCESS");
  }

  xTaskCreatePinnedToCore(sendData,   /* Function to implement the task */
                          "sendData", /* Name of the task */
                          4096,       /* Stack size in words */
                          NULL,       /* Task input parameter */
                          configMAX_PRIORITIES - 1, /* Priority of the task */
                          NULL,                     /* Task handle. */
                          0); /* Core where the task should run */
  xTaskCreate(blinkLEDInSensorRead, "blinkLED", 1024, NULL, 1, NULL);
}

void loop() {
  // Make sure to call update as fast as possible
  pox.update();

  bpm = pox.getHeartRate();
  spo2 = pox.getSpO2();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    if (bpm > 0 && spo2 > 0) {
      Serial.print("Heart rate:");
      Serial.print(bpm);
      Serial.print("bpm / SpO2:");
      Serial.print(spo2);
      Serial.println("%");
    }
    tsLastReport = millis();
  }

  delay(5);
}

void sendData(void *parameter) {
  while (1) {

    if (millis() - tsLastDataSend > REPORTING_PERIOD_MS) {
      if (spo2 > 0 && bpm > 0) {
        request_body["user_id"] = 0;
        request_body["bpm"] = (int)bpm;
        request_body["spo2"] = (int)spo2;
        request_body["date"] = DateTime.format("%FT%T");

        String request_body_payload;
        serializeJson(request_body, request_body_payload);

        HTTPClient http;
        // Your Domain name with URL path or IP address with path
        http.begin(serverName);

        Serial.printf("REQUEST BODY: %s\n", request_body_payload.c_str());
        http.addHeader("Content-Type", "application/json");
        int code = http.POST(request_body_payload);
        Serial.println("STATUS CODE:");
        Serial.println(code);
        Serial.println("PAYLOAD:");
        Serial.println(http.getString());

        http.end();
      }
      tsLastDataSend = millis();
    }
    delay(1);
  }
  vTaskDelete(NULL);
}

void blinkLEDInSensorRead(void *parameter) {
  while (1) {
    if (bpm > 0 && spo2 > 0) {
      blinkLED(500);
    }
    delay(500);
  }

  vTaskDelete(NULL);
}
