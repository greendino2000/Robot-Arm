#include <AccelStepper.h>
#include <Servo.h>

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

// Standby toggle
// #define STBY_PIN 2

#define STEPS_PER_REVOLUTION 200

AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);
Servo servos[] = {Servo(), Servo(), Servo(), Servo()};
const int numServos = sizeof(servos) / sizeof(servos[0]);

// Define RoutineStep structure
struct RoutineStep {
  int stepperPosition;
  int servoPositions[numServos];
};

// Define routines
RoutineStep routine1[] = {
  {1, {100, 30, 90, 90}},
};

RoutineStep routine2[] = {
  {0, {135, 140, 80, 85}},
  {0, {70, 65, 20, 150}},
  {0, {70, 65, 20, 95}},
  {0, {135, 120, 80, 95}},
  {50, {60, 80, 50, 95}},
  {50, {60, 80, 50, 150}},
  {50, {135, 140, 80, 85}},
  {0, {100, 25, 150, 90}},
};

const int INTERPOLATION_STEPS = 15;  // Controls the smoothness of routines

/**
 * Initializes the setup of the robot arm sketch, including setting up the serial communication, stepper motor, and servos.
 */
void setup() {
  Serial.begin(9600);

  // pinMode(STBY_PIN, OUTPUT);
  // digitalWrite(STBY_PIN, HIGH); // Enable the stepper initially
  
  stepper.setMaxSpeed(250);
  stepper.setAcceleration(125);
  stepper.setCurrentPosition(0);

  // Attaches servos to pins
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(SERVO1_PIN + i);
  }

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
  if (targetPosition > 200) {
    targetPosition = 200;
  }
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
    servos[servoIndex].write(position);
    Serial.print("Servo ");
    Serial.print(servoIndex + 1);
    Serial.print(" Position: ");
    Serial.println(position);
  }
  else {
    Serial.println("Invalid servo position");
    break;
  }
}

/**
 * Executes a routine by moving the stepper motor to the specified position and interpolating the servo positions.
 * @param routine An array of RoutineStep objects that define the positions of the stepper motor and servos for each step of the routine.
 * @param numSteps The number of steps in the routine.
 */
void executeRoutine(RoutineStep *routine, int numSteps) {
  // digitalWrite(STBY_PIN, HIGH); // Enable motors before executing routine

  for (int step = 0; step < numSteps; step++) {
    moveStepperToPosition(routine[step].stepperPosition);
    
    // Creates an array of the initial servo positions for intepolation calculations
    int initialServoPositions[numServos];
    for (int i = 0; i < numServos; i++) {
      initialServoPositions[i] = servos[i].read();
    }
    
    // Interpolates between current and desired servo positions and sets them
    for (int i = 1; i <= INTERPOLATION_STEPS; i++) {
      for (int servoIndex = 0; servoIndex < numServos; servoIndex++) {
        int interpolatedPosition = initialServoPositions[servoIndex] + ((routine[step].servoPositions[servoIndex] - initialServoPositions[servoIndex]) * i / INTERPOLATION_STEPS);
        setServoPosition(servoIndex, interpolatedPosition);
      }
      delay(50); // Add a small delay between each interpolation step
    }
    
    // Sets the final servo positions
    for (int servoIndex = 0; servoIndex < numServos; servoIndex++) {
      setServoPosition(servoIndex, routine[step].servoPositions[servoIndex]);
    }
    
    delay(1000); // Delay between steps
  }
  
  // digitalWrite(STBY_PIN, LOW); // Put motors in standby after moving
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
        setServoPosition(2, value);
        break;
      case 'E':
        setServoPosition(3, value);
        break;
      case '1': // Execute routine 1
        executeRoutine(routine1, sizeof(routine1) / sizeof(routine1[0]));
        break;
      case '2': // Execute routine 2
        executeRoutine(routine2, sizeof(routine2) / sizeof(routine2[0]));
        break;
      default:
        // Handle unknown command
        break;
    }
  }
}

void loop() {
  processSerialInput();
}
