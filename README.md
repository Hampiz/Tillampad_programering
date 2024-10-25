# Tillampad_programering
 This Arduino project controls a clock and temperature monitoring system, which also manages a fan, buzzer, and servo motor based on the temperature readings. Here’s a breakdown of the main parts of the code:

Libraries and Constants
Libraries:
RTClib.h: Interfaces with the DS3231 real-time clock (RTC).
Wire.h: Enables I2C communication, used by the RTC and OLED.
Servo.h: Controls the servo motor.
U8glib.h: Controls the OLED display.

Constants:
tempThreshold is set to 22 °C. It’s the temperature threshold for activating the buzzer and fan.
Objects and Pin Definitions
RTC: RTC_DS3231 rtc manages the DS3231 RTC module.
Servo: myServo controls the servo motor, attached to servoPin (pin 9).
Buzzer and Relay Pins: buzzerPin (pin 10) and relayPin (pin 8) control the buzzer and fan, respectively.
OLED: U8GLIB_SSD1306_128X64 u8g initializes the OLED display (128x64 resolution).

setup() Function
The setup() function initializes all the components:
Serial Communication: Initializes serial for monitoring.
RTC: Starts the RTC, sets the time to the current date and time based on the system.
Servo, Buzzer, and Relay: Configures pins for the servo, buzzer, and relay, and initializes the relay (fan) to LOW (off).

loop() Function
The loop() function runs continuously:
Time and Temperature Retrieval: Gets the current time from the RTC and the temperature using getTemp().
Serial Output: Prints the time and temperature to the serial monitor.
OLED Display: Updates the OLED display using oledWrite().
Servo Positioning: Adjusts the servo based on temperature using servoWrite().
Buzzer and Fan Control: Uses checkTemperature() to activate the buzzer and fan if the temperature exceeds tempThreshold.

Helper Functions
getTime(): Formats time into hh:mm:ss format for easier display.
getTemp(): Reads the temperature from the DS3231 RTC module.
oledWrite(): Writes both time and temperature to the OLED display.
Starts by calling u8g.firstPage() and continues writing each page of the display with u8g.nextPage().
servoWrite(): Maps the current temperature to an angle for the servo motor, within the range of 0 to 180 degrees.
checkTemperature(): Controls the fan and buzzer based on the current temperature:
Activates the buzzer and fan if the temperature is above tempThreshold.
Deactivates both if the temperature falls below tempThreshold.
