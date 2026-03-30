# Drone Weather Station

Source code for the paper [Integrating a Weather Station on a Drone: A Prototype for Enhanced Atmospheric Data Collection](https://www.researchgate.net/publication/403263221_Integrating_a_Weather_Station_on_a_Drone_A_Prototype_for_Enhanced_Atmospheric_Data_Collection).

An ESP32 firmware that reads atmospheric data from onboard sensors and serves it over Wi-Fi via a simple HTTP server.

## Sensors

| Sensor | Measurement | GPIO |
|---|---|---|
| DHT11 | Temperature & Humidity | 4 |
| BMP180 | Barometric Pressure | I2C |
| Rain Sensor | Rainfall Detection | 33 |
| LDR | Light Intensity | 34 |

## Dependencies

- Adafruit Unified Sensor
- DHT sensor library
- Adafruit BMP085/BMP180

## Setup

1. Install the dependencies via the Arduino Library Manager.
2. Update the Wi-Fi credentials in the sketch.
3. Flash to the ESP32 and navigate to the device IP in a browser to view readings.

## License

MIT
