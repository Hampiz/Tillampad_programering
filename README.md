# Tillampad_programering
Project Overview

Project Name: Clock and Temperature Project with Buzzer and Fan

Author: Hampus Bengtsson

Date: 2024-10-25

Description

This project integrates a DS3231 Real-Time Clock (RTC) module to measure and display time on a 1306 OLED display. In addition to timekeeping, the system monitors ambient temperature and controls various components, including a servo motor, buzzer, and fan, based on the temperature readings.

Components and Libraries Used

Hardware:

DS3231 RTC module for time and temperature measurement
SSD1306 OLED display for user interface
Servo motor for physical control based on temperature
Buzzer for audio alerts
Relay module to control the fan

Libraries:

RTClib for interacting with the DS3231 module
Wire for I2C communication
Servo for controlling the servo motor
U8glib for driving the OLED display

Functionality

Time Display: The RTC module retrieves the current time, which is displayed in the format hh:mm:ss on the OLED screen and the serial monitor.

Temperature Measurement: The project continuously measures the ambient temperature using the DS3231 module and displays it alongside the time.

Servo Control: The servo motor's position is adjusted based on the temperature reading, where temperatures are mapped to angles between 0 and 180 degrees.

Buzzer and Fan Control: 

A predefined temperature threshold (22°C) is set to activate the buzzer and fan. When the temperature exceeds this threshold, the buzzer sounds a tone at 250 Hz, and the fan is activated via a relay. Conversely, if the temperature falls below the threshold, both the buzzer and fan are turned off.

Code Structure

The setup() function initializes communication, sets up the RTC, attaches the servo, and configures the buzzer and relay pins.

The loop() function continuously fetches the current time and temperature, updates the OLED display, adjusts the servo position, and checks the temperature to control the buzzer and fan accordingly.

Helper functions:

getTime(DateTime now) formats the time string.
getTemp() retrieves the current temperature from the RTC module.
oledWrite(DateTime now) updates the OLED display with the time and temperature.
servoWrite(float temperature) maps the temperature to a servo angle.
checkTemperature(float temperature) manages the activation of the buzzer and fan based on the temperature threshold.

Conclusion

This project effectively combines timekeeping and environmental monitoring in a compact system. It demonstrates the use of multiple components working in unison to provide real-time data and responsive control based on temperature, making it suitable for various applications, such as smart home systems or climate control projects.
