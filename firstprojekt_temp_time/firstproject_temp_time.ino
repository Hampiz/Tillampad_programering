/*
* Name: Clock and temp project with buzzer and fan
* Author: Hampus Bengtsson
* Date: 2024-10-25
* Description: This project uses a DS3231 to measure time and display it on a 1306 OLED display.
* It also measures temperature with a DS3231 module, and controls a servo motor, a buzzer, and a fan based on the temperature.
*/

// Include Libraries 
#include <RTClib.h>
#include <Wire.h>
#include <Servo.h>
#include <U8glib.h>

// Init constants
const float tempThreshold = 22;

// Construct objects
RTC_DS3231 rtc;
Servo myServo;
const int servoPin = 9;
const int buzzerPin = 10;
const int relayPin = 8; 
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  // Init communication
  Serial.begin(9600);
  Wire.begin();
  
  // Init Hardware
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  myServo.attach(servoPin); 
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  DateTime now = rtc.now();
  
  // Show time and temperature on the serial monitor
  Serial.println("Time: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
  float temp = getTemp();
  Serial.println("Temperature: " + String(temp) + "C");

  // Update the OLED-screen
  oledWrite(now);

  // Servo based on temperature
  servoWrite(temp);

  // Control piezo and fan via relay based on temperature
  checkTemperature(temp);
  
  delay(1000);
}

/*
* This function reads time from a DS3231 module and packages the time as a String
* Parameters: Void
* Returns: time in hh:mm:ss as String
*/
String getTime(DateTime now) { 
  // If the number is below 10, it adds a zero in front of it so it's in the hh:mm:ss format
  String hourString = now.hour() < 10 ? "0" + String(now.hour()) : String(now.hour()); 
  String minuteString = now.minute() < 10 ? "0" + String(now.minute()) : String(now.minute());
  String secondString = now.second() < 10 ? "0" + String(now.second()) : String(now.second());

  return hourString + ":" + minuteString + ":" + secondString;
}

/*
* This function reads the temperature from a DS3231 module
* Parameters: Void
* Returns: temperature as float
*/
float getTemp() {
  return rtc.getTemperature();
}

/*
* This function writes the time and temperature to an OLED display
* Parameters: - now: DateTime object containing current time
* Returns: void
*/
void oledWrite(DateTime now) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);

    // Get the time and write it on the screen
    String timeStr = "Time: " + getTime(now);
    u8g.drawStr(4, 15, timeStr.c_str());

    // Get the temperature and write it on the screen
    String tempStr = "Temperature: " + String(getTemp()) + "C";
    u8g.drawStr(4, 40, tempStr.c_str());

  } while (u8g.nextPage());
}

/*
* Takes a temperature value and maps it to the corresponding degree on a servo
* Parameters: - temperature: the current temperature
* Returns: void
*/
void servoWrite(float temperature) {
  int angle = map(temperature, 15, 30, 0, 180);
  angle = constrain(angle, 0, 180);

  myServo.write(angle);
}

/*
* This function controls the buzzer and fan via relay based on the temperature
* Parameters: - temperature: the current temperature
* Returns: void
*/
void checkTemperature(float temperature) {
  if (temperature > tempThreshold) {
    // Activate the buzzer if the temperature is above the threshold
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 250); // Tone of 250 Hz

    // Activate the fan
    digitalWrite(relayPin, HIGH);
  } else {
    // Deactivate the buzzer and fan via relay if temperature is below threshold
    digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);

    digitalWrite(relayPin, LOW);
  }
}
