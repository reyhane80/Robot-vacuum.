
#include <NewPing.h>




#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200 


#define MOTOR_A_PIN  3
#define MOTOR_B_PIN  4


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
}

void loop() {
  iterativeDeepeningSearch();
}

void iterativeDeepeningSearch() {
  int limit = 1; 
  bool exitFound = false;

  while (!exitFound) {
    exitFound = depthFirstSearch(0, limit, 0);
    limit++; 
}

bool depthFirstSearch(int depth, int limit, int zeroCounter) {
  if (depth >= limit) return false; 
  
  unsigned int distance = sonar.ping_cm();
  if (distance == 0 || distance > MAX_DISTANCE) {
    zeroCounter++;
    if (zeroCounter == 2) {
      
      return true;
    }
  } else {
    zeroCounter = 0; 
  }

  
  moveForward();

  
  if (depthFirstSearch(depth + 1, limit, zeroCounter)) {
    return true;
  }

  
  moveBackward();

  
 

  return false; 

void moveForward() {
  digitalWrite(MOTOR_A_PIN, HIGH);
  digitalWrite(MOTOR_B_PIN, LOW);
  delay(100); 
}

void moveBackward() {
  digitalWrite(MOTOR_A_PIN, LOW);
  digitalWrite(MOTOR_B_PIN, HIGH);
  delay(100); 
