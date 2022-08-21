# Oximeter Monitor with ESP32 and MAX30100

Project made for my Microcontrollers class, the goal of this project is to collect the heartrate and oxygen saturation data using the ESP32 microcontroller
and the MAX30100 sensor. The whole project is divided into 3 parts/repositories: the microcontroller firmware (this repository), the [REST Api](https://github.com/LaBatata101/oximeter-rest-api) for the data management and the [Telegram bot](https://github.com/LaBatata101/oximeter-telegram-bot) for real time data visualization.

In this repository you will find the code for the ESP32 firmware that will be responsible for collecting the data from the sensor and sending it to the database through the REST Api, this firmware also implements a WebServer for real time visualization of the data being collected, the user needs to be
connected to the same network as the ESP32 to access the web page, this page can be accessed via the `http://oximetro.local` URL.

Bellow you can see the circuit diagram:

![image](https://user-images.githubusercontent.com/20308796/185767820-c568fc87-07f3-4737-a4bf-cee4043f3049.png)

Visualization of the collected data with the web page hosted in the ESP32:

![image](https://user-images.githubusercontent.com/20308796/185768137-be24fe47-a4ee-4b36-8247-a15a35b8b853.png)

## How to build the project
**Dependencies:**
- oxullo/MAX30100lib 1.2.1
-	kontakt/MAX30100 1.0
-	bblanchon/ArduinoJson 6.19.4
-	me-no-dev/ESP Async WebServer 1.2.3
-	mcxiaoke/ESPDateTime 1.0.4


Clone the project:
```bash
$ git clone https://github.com/LaBatata101/oximeter-esp32-firmware
```

You can build the project and flash it to the ESP32 using the VSCode extension [PlatformIO](https://platformio.org/).

Or using the [IDF Frontend](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-py.html).

Or using the [Arduino IDE](https://www.arduino.cc/en/software/).
