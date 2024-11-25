#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ENABLE true
#define DISABLE false

#define FRONT 0
#define LEFT 1
#define RIGHT 2

typedef enum {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  HALTS,
} cleanerMotion;

typedef enum {
  POWER_UP = 5,
  POWER_ON,
  POWER_OFF,
} cleanerPowerOption;

// initialize obstacles location and dust existence
bool frontObstacle = false;
bool leftObstacle = false;
bool rightObstacle = false;

bool dustExistence = false;

// initialize motion and power option of RVC
cleanerMotion motion = MOVE_FORWARD;
cleanerPowerOption power = POWER_ON;

// generates random number in range
int generateRandomNumberInRange(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void turnLeftInterface() { motion = TURN_LEFT; }
void turnRightInterface() { motion = TURN_RIGHT; }

void moveBackwardInterface() { motion = MOVE_BACKWARD; }
void moveForwardInterface(bool enable) {
  if (enable)
    motion = MOVE_FORWARD;
  else
    motion = HALTS;
}

void powerUpInterface() { power = POWER_UP; }
void powerOnInterface() { power = POWER_ON; }
void powerOffInterface() { power = POWER_OFF; }

bool frontSensorInterface() { return false; }
bool leftSensorInterface() { return false; }
bool rightSensorInterface() { return false; }
bool dustSensorInterface() { return false; }

void turnLeft() {
  moveForwardInterface(DISABLE);
  powerOffInterface();
  turnLeftInterface();
}

void turnRight() {
  moveForwardInterface(DISABLE);
  powerOffInterface();
  turnRightInterface();
}

void moveBackward() {
  moveForwardInterface(DISABLE);
  powerOffInterface();
  moveBackwardInterface();
  turnLeft();
}

void moveForward() {
  powerOnInterface();
  moveForwardInterface(ENABLE);
}
void powerUpAndMoveForward() {
  powerUpInterface();
  moveForwardInterface(ENABLE);
}

// Determine obstacle locations

bool *determineObstacleLocation() {
  bool *obstacleLocations = (bool *)malloc(sizeof(bool) * 3);

  if (frontSensorInterface())
    obstacleLocations[FRONT] = true;
  if (leftSensorInterface())
    obstacleLocations[LEFT] = true;
  if (rightSensorInterface())
    obstacleLocations[RIGHT] = true;

  return obstacleLocations;
}

bool determineDustExistence() { return dustSensorInterface(); }

// A function that counts 5-ticks
// If a location of obstacles is fixed, it just loops 5 times and terminates
// Else, it determines a location of obstacles at every step of the loop
// then decide the next motion of RVC

void tickFiveSeconds(bool obstaclesAreFixed, bool *obstacleLocations) {}

// The main controller of RVC
// Since we have decided that there is no branch to terminate the RVC after turn
// it on, it infinitely loops

void controller() {
  while (true) {
    bool *obstacleLocations;
    bool dustExsitence = false;
    obstacleLocations = determineObstacleLocation();
    dustExistence = determineDustExistence();
    if (dustExistence) {
      powerUpAndMoveForward();
    } else if (obstacleLocations[FRONT]) {
      turnLeft();
      // tick-5.. and obstacles location is fixed
      // tickFiveSeconds(true);
    } else if (obstacleLocations[FRONT] && obstacleLocations[LEFT]) {
      turnRight();
      // tick-5.. and obstacles location is fixed
      // tickFiveSeconds(true);
    } else if (obstacleLocations[FRONT] && obstacleLocations[LEFT] &&
               obstacleLocations[RIGHT]) {
      moveBackward();
      // tick-5 .. and obstacles location is fixed
      // tickFiveSeconds(true);
      turnLeft();
    }
    // Here we assume that cleaner's motion is fixed to move forward
    else
      moveForward();
  }
}
