#include <Arduino.h>
#include <Servo.h>

// Constants
const int VOLTAGE_SENSOR_PIN = A0;
const int SERVO_PIN = 9;
const int SERVO_CLOCKWISE_POSITION = 110;  // Clockwise position
const int SERVO_COUNTERCLOCKWISE_POSITION = 134;  // Counterclockwise position
const int SERVO_NEUTRAL_POSITION = 122;  // Neutral position
const int VOLTAGE_THRESHOLD_CLOCKWISE = 300;  // Threshold for clockwise actuation
const int VOLTAGE_THRESHOLD_COUNTERCLOCKWISE = 150;  // Threshold for counterclockwise actuation
const bool DEBUG_OUTPUT = true;

// Servo object
Servo myServo;

void setup() {
  if (DEBUG_OUTPUT) {
    Serial.begin(9600);
  }
  
  myServo.attach(SERVO_PIN);
  if (!myServo.attached()) {
    // Handle servo attachment error
  }
  
  // Initialize servo to neutral position
  myServo.write(SERVO_NEUTRAL_POSITION);
}

void loop() {
  int voltageValue = (int)analogRead(VOLTAGE_SENSOR_PIN);
  
  if (DEBUG_OUTPUT) {
    Serial.print("Voltage Value: ");
    Serial.println(voltageValue);
  }
  
  if (VOLTAGE_THRESHOLD_CLOCKWISE >= voltageValue && voltageValue >= VOLTAGE_THRESHOLD_COUNTERCLOCKWISE ) {
    // Actuate counterclockwise
    myServo.write(SERVO_COUNTERCLOCKWISE_POSITION);
  } else if (voltageValue > VOLTAGE_THRESHOLD_CLOCKWISE) {
    // Actuate clockwise
    myServo.write(SERVO_CLOCKWISE_POSITION);
  } else {
    // Return to neutral position
    myServo.write(SERVO_NEUTRAL_POSITION);
  }
  
  delay(15); // Consider replacing with a more precise timing mechanism
}