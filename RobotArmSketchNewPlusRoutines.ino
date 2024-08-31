#include <AccelStepper.h>
#include "ServoEasing.hpp"

// Stepper motor pins
#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 9
#define MOTOR_PIN_3 10
#define MOTOR_PIN_4 11

// First arm segment servo
#define SERVO1_PIN 4
// Second arm segment servo
#define SERVO2_PIN 5
// Claw joint rotation servo
#define SERVO3_PIN 6
// Claw open/close servo
#define SERVO4_PIN 7

#define STEPS_PER_REVOLUTION 200
#define NUM_SERVOS 4

int delayTime = 1000;

AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);
ServoEasing servos[NUM_SERVOS];

// Define RoutineStep structure
struct RoutineStep {
  int stepperPosition;
  int servoPositions[NUM_SERVOS];
};

// Define routines
RoutineStep routine1[] = { // Vertical
  {1, {90, 0, 100, 90}},
};

RoutineStep routine2[] = { // 90 deg grab
  {0, {140, 140, 100, 90}},
  {0, {20, 65, 55, 130}},
  {0, {20, 65, 55, 80}},
  {0, {140, 140, 100, 80}},
  {50, {20, 55, 55, 80}},
  {50, {20, 55, 55, 130}},
  {50, {140, 130, 100, 90}},
  {0, {90, 0, 100, 90}},
};

RoutineStep routine3[] = { // Fold
  {0, {140, 140, 100, 90}},
};

RoutineStep routine4[] = { // 90 deg grab adjusted
  {0, {140, 140, 100, 90}},
  {0, {5, 55, 50, 130}},
  {0, {5, 55, 50, 75}},
  {0, {140, 140, 100, 75}},
  {50, {5, 55, 50, 75}},
  {50, {5, 55, 50, 130}},
  {50, {140, 130, 100, 90}},
  {0, {90, 0, 100, 90}},
};

void setup() {
  Serial.begin(9600);
  
  stepper.setMaxSpeed(250);
  stepper.setAcceleration(125);
  stepper.setCurrentPosition(0);

  // Attach servos to pins
  servos[0].attach(SERVO1_PIN);
  servos[1].attach(SERVO2_PIN);
  servos[2].attach(SERVO3_PIN);
  servos[3].attach(SERVO4_PIN);

  // Set default servo speed
  setSpeedForAllServos(180);

  // Move to upright position
  executeRoutine(routine1, sizeof(routine1) / sizeof(routine1[0]));
}

/**
 * Moves the stepper motor to the specified target position.
 * If the target position is greater than 200, it sets the target position to 200.
 * Blocks until the motor reaches the target position.
 * Prints the current position of the motor to the serial monitor.
 *
 * @param targetPosition The target position to move the stepper motor to.
 */
void moveStepperToPosition(int targetPosition) {
  if (targetPosition > 200) {targetPosition = 200;}
  stepper.moveTo(targetPosition);
  while (stepper.isRunning()) {
    stepper.run();
  }
  Serial.print("Current Position: ");
  Serial.println(stepper.currentPosition());
}

/**
 * Sets the position of a servo.
 * 
 * @param servoIndex The index of the servo motor to set the position for.
 * @param position The position to set the servo motor to.
 */
void setServoPosition(int servoIndex, int position) {
  if (position >= 0 && position <= 180) {
    servos[servoIndex].easeTo(position);
    Serial.print("Servo ");
    Serial.print(servoIndex + 1);
    Serial.print(" Position: ");
    Serial.println(position);
  }
  else {
    Serial.println("Invalid servo position");
  }
}

/**
 * Executes a routine by moving the stepper motor to the specified position and interpolating the servo positions.
 * @param routine An array of RoutineStep objects that define the positions of the stepper motor and servos for each step of the routine.
 * @param numSteps The number of steps in the routine.
 */
void executeRoutine(RoutineStep *routine, int numSteps) {
  for (int step = 0; step < numSteps; step++) {
    moveStepperToPosition(routine[step].stepperPosition);
    
    // Set target positions for all servos
    for (int servoIndex = 0; servoIndex < NUM_SERVOS; servoIndex++) {
      servos[servoIndex].setEaseTo(routine[step].servoPositions[servoIndex]);
    }
    
    // Start and synchronize all servo movements
    synchronizeAllServosStartAndWaitForAllServosToStop();
    
    delay(delayTime); // Delay between steps
  }
}



/**
 * This function reads serial input and performs actions based on the received character.
 * The function reads the character and an integer value from the serial port and performs the following actions:
 * - 'A': Moves the stepper motor to the specified position.
 * - 'B': Sets the position of servo 0 to the specified value.
 * - 'C': Sets the position of servo 1 to the specified value.
 * - 'D': Sets the position of servo 2 to the specified value.
 * - 'E': Sets the position of servo 3 to the specified value.
 * - '1': Executes routine 1.
 * - '2': Executes routine 2.
 * If an unknown command is received, it is ignored.
 */
void processSerialInput() {
  while (Serial.available()) {
    char receivedChar = Serial.read();
    int value = Serial.parseInt();
    
    switch (receivedChar) {
      // Individual motor control
      case 'A':
        moveStepperToPosition(value);
        break;
      case 'B':
        setServoPosition(0, value);
        break;
      case 'C':
        setServoPosition(1, value);
        break;
      case 'D':
        if(isUpperCase(receivedChar)) {
          setServoPosition(2, value);
        }
        break;
      case 'E':
        setServoPosition(3, value);
        break;
      // WebUI Functions
      case 's': // Set speed
        setSpeedForAllServos(value);
        Serial.print("Speed set to: ");
        Serial.println(value);
        break;
      case 'd': // Set delay
        if(!isUpperCase(receivedChar)) {
          delayTime = value;
          Serial.print("Step delay set to: ");
          Serial.println(value);
        }
        break;
      // Hardcoded routines
      case '1': // Execute routine 1
        executeRoutine(routine1, sizeof(routine1) / sizeof(routine1[0]));
        break;
      case '2': // Execute routine 2
        executeRoutine(routine2, sizeof(routine2) / sizeof(routine2[0]));
        break;
      case '3': // Execute routine 3
        executeRoutine(routine3, sizeof(routine3) / sizeof(routine3[0]));
        break;
      case '4': // Execute routine 4
        executeRoutine(routine4, sizeof(routine4) / sizeof(routine4[0]));
        break;
      // Fallback
      default:
        // Handle unknown command
        break;
    }
  }
}

void loop() {
  processSerialInput();
}
