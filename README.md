# Environmental and Light Sensors with OLED Display

![Platform](https://img.shields.io/badge/platform-Arduino-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-informational)
![Sensors](https://img.shields.io/badge/sensors-BME680%20%7C%20TMG39931-green)
![Display](https://img.shields.io/badge/display-OLED-lightgrey)
![Status](https://img.shields.io/badge/status-Working-success)

## Description

This project uses a microcontroller board to read environmental and light data, then display it on an integrated OLED screen.

Two sensors are used:
- a RGB light sensor (TMG39931)
- an environmental sensor (BME680) measuring temperature, humidity, pressure, and air quality

The display automatically alternates between light data and environmental data.

## Features

- Reads red, green, and blue light values  
- Measures temperature, humidity, pressure, and gas levels  
- Displays data on an OLED screen  
- Automatically switches between data views  
- Uses two separate I2C buses  

## Hardware

- Arduino-compatible board with OLED display  
- BME680 sensor  
- TMG39931 sensor  

## Setup

1. Clone the repository  
2. Open the project in the Arduino IDE  
3. Install the required libraries:  
   - Adafruit BME680  
   - Adafruit Sensor  
   - SSD1306Wire  
4. Upload the code to the board  

## Usage

Once the program is running, the screen alternates between:  
- RGB light sensor values  
- Environmental data (temperature, humidity, pressure, gas)  

## Project Overview

### Hardware setup

![Hardware setup](images/setup.jpg)

### OLED display output

![OLED display](images/display.jpg)

## Notes

Make sure the sensors are properly connected to the correct I2C pins.  
The display refreshes every few seconds and switches between the two data screens automatically.
