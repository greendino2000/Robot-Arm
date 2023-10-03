#include <AccelStepper.h>
#include <Servo.h>

#define MOTOR_PIN_1 8
#define MOTOR_PIN_2 9
#define MOTOR_PIN_3 10
#define MOTOR_PIN_4 11

// First arm segment servo
#define SERVO1_PIN 4
// Second arm segment servo
#define SERVO2_PIN 5
// Claw open/close servo
#define SERVO3_PIN 6
// Claw joint rotation servo
#define SERVO4_PIN 7

// Standby toggle
// #define STBY_PIN 2

#define STEPS_PER_REVOLUTION 200

AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);
Servo servos[] = {Servo(), Servo(), Servo(), Servo()};
const int numServos = sizeof(servos) / sizeof(servos[0]);

int currentPosition = 0;

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
  {0, {135, 140, 85, 80}},
  {0, {70, 65, 150, 20}},
  {0, {70, 65, 95, 20}},
  {0, {135, 120, 95, 80}},
  {50, {60, 80, 95, 50}},
  {50, {60, 80, 150, 50}},
  {50, {135, 140, 85, 80}},
  {0, {100, 25, 90, 150}},
};

const int INTERPOLATION_STEPS = 20;  // Controls the smoothness of routines

void setup() {
  Serial.begin(9600);

  // pinMode(STBY_PIN, OUTPUT);
  // digitalWrite(STBY_PIN, HIGH); // Enable the stepper initially
  
  stepper.setMaxSpeed(250);
  stepper.setAcceleration(125);
  stepper.setCurrentPosition(0);

  for (int i = 0; i < numServos; i++) {
    servos[i].attach(SERVO1_PIN + i);
  }

  executeRoutine(routine1, sizeof(routine1) / sizeof(routine1[0]));
}

void moveStepperToPosition(int targetPosition) {
  if (targetPosition > 200) {
    targetPosition = 200;
  }
  stepper.moveTo(targetPosition);
  while (stepper.isRunning()) {
    stepper.run();
  }
  currentPosition = stepper.currentPosition();
  Serial.print("Current Position: ");
  Serial.println(currentPosition);
}

void setServoPosition(int servoIndex, int position) {
  if (position >= 0 && position <= 180) {
    servos[servoIndex].write(position);
    Serial.print("Servo ");
    Serial.print(servoIndex + 1);
    Serial.print(" Position: ");
    Serial.println(position);
  }
}

void executeRoutine(RoutineStep *routine, int numSteps) {
  // digitalWrite(STBY_PIN, HIGH); // Enable motors before executing routine

  for (int step = 0; step < numSteps; step++) {
    moveStepperToPosition(routine[step].stepperPosition);
    
    int initialServoPositions[numServos];
    for (int i = 0; i < numServos; i++) {
      initialServoPositions[i] = servos[i].read();
    }
    
    for (int i = 1; i <= INTERPOLATION_STEPS; i++) {
      for (int servoIndex = 0; servoIndex < numServos; servoIndex++) {
        int interpolatedPosition = initialServoPositions[servoIndex] + ((routine[step].servoPositions[servoIndex] - initialServoPositions[servoIndex]) * i / INTERPOLATION_STEPS);
        setServoPosition(servoIndex, interpolatedPosition);
      }
      delay(50); // Add a small delay between each interpolation step
    }
    
    for (int servoIndex = 0; servoIndex < numServos; servoIndex++) {
      setServoPosition(servoIndex, routine[step].servoPositions[servoIndex]);
    }
    
    delay(1000); // Delay between steps
  }
  
  // digitalWrite(STBY_PIN, LOW); // Put motors in standby after moving
}

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
