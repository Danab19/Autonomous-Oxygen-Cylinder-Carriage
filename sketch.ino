#include "AIVision.h" // Including the AIVision library header file
#include <Servo.h> // Including the Servo library
#include <Ultrasonic.h> // Including the Ultrasonic library

AIVision aiVision; // Creating an instance of the AIVision class
Ultrasonic ultrasonic(6, 7); // Creating an instance of the Ultrasonic class with trigger pin 6 and echo pin 7
Servo servoR; // Creating an instance of the Servo class for the right servo motor
Servo servoL; // Creating an instance of the Servo class for the left servo motor

int centerX = 160, centerY = 120; // Initializing the center coordinates of the screen
int distance; // Variable to store the distance measured by the ultrasonic sensor
int speedR; // Variable to store the speed for the right servo motor
int speedL; // Variable to store the speed for the left servo motor
int x_position, y_position; // Variables to store the coordinates of the detected object

void setup() {
  Serial.begin(9600); // Initializing serial communication with baud rate 9600
  aiVision.begin(); // Initializing the AIVision module

  servoR.attach(10); // Attaching the right servo motor to pin 10
  servoL.attach(9); // Attaching the left servo motor to pin 9

  servoR.write(90); // Setting the initial position of the right servo motor to stop
  servoL.write(90); // Setting the initial position of the left servo motor to stop
}

void loop() {
  int Object = aiVision.getID(); // Getting the ID of the detected object from the AIVision module
  Serial.println(Object); // Printing the ID of the detected object to serial monitor for debugging
  aiVision.getCoordinates(x_position, y_position); // Getting the coordinates of the detected object

  // If no object is detected, stop both servo motors
  if (Object == -1) {
    servoR.write(90); // Stopping the right servo motor
    servoL.write(90); // Stopping the left servo motor
  } else { // If an object is detected, track it
    distance = ultrasonic.read(); // Reading the distance measured by the ultrasonic sensor

    // If the object is too close, stop both servo motors
    if (distance <= 15) {
      speedR = 90; // Stop the right servo motor
      speedL = 90; // Stop the left servo motor
    } else {
      // Adjusting servo motor speeds based on the x_position of the object
      if (x_position > 230) {
        speedR = 90; // Stop the right servo motor
        speedL = 180; // Move the left servo motor forward
      } else if (x_position < 70) {
        speedR = 0; // Move the right servo motor forward
        speedL = 90; // Stop the left servo motor
      } else {
        speedR = 0; // Move the right servo motor forward
        speedL = 180; // Move the left servo motor forward
      }
    }

    // Apply the calculated speeds to the servo motors
    servoR.write(speedR); // Setting the speed for the right servo motor
    servoL.write(speedL); // Setting the speed for the left servo motor

    delay(100); // Delay in milliseconds to adjust the tracking speed based on your needs
  }
}
