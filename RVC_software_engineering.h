#include "venv.h"

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

bool callTurnLeftInterface = false;
bool callTurnRightInterface = false;
bool callMoveForwardInterface = false;
bool callMoveBackwardInterface = false;
bool callPowerUpAndMoveForwardInterface = false;

// initialize motion and power option of RVC
cleanerMotion motion = MOVE_FORWARD;
cleanerPowerOption power = POWER_ON;

void resetTestCondition() {
  callMoveBackwardInterface = false;
  callMoveForwardInterface = false;
  callTurnLeftInterface = false;
  callTurnRightInterface = false;
}

void turnLeftInterface() {
  callTurnLeftInterface = true;
  motion = TURN_LEFT;
}
void turnRightInterface() {
  callTurnRightInterface = true;
  motion = TURN_RIGHT;
}

void moveBackwardInterface() {
  callMoveBackwardInterface = true;
  motion = MOVE_BACKWARD;
}

void moveForwardInterface(bool enable) {
  callMoveForwardInterface = true;
  if (enable)
    motion = MOVE_FORWARD;
  else
    motion = HALTS;
}

void powerUpInterface() { power = POWER_UP; }
void powerOnInterface() { power = POWER_ON; }
void powerOffInterface() { power = POWER_OFF; }

bool frontSensorInterface() { return venvFrontObstacle; }
bool leftSensorInterface() { return venvLeftObstacle; }
bool rightSensorInterface() { return venvRightObstacle; }
bool dustSensorInterface() { return venvFrontDust; }

void turnLeft() {
  for (int i = 0; i < 5; ++i) {
    moveForwardInterface(DISABLE);
    powerOffInterface();
    turnLeftInterface();
  }
}

void turnRight() {
  for (int i = 0; i < 5; ++i) {
    moveForwardInterface(DISABLE);
    powerOffInterface();
    turnRightInterface();
  }
}

void moveBackward() {
  for (int i = 0; i < 5; ++i) {
    moveForwardInterface(DISABLE);
    powerOffInterface();
    moveBackwardInterface();
  }
}

void moveForward() {
  powerOnInterface();
  moveForwardInterface(ENABLE);
}

void powerUpAndMoveForward() {
  powerUpInterface();
  moveForwardInterface(ENABLE);
}

/**
 * @brief Determine where the obstacles are.
 */
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

/**
 * @brief Determine the existence of dust.
 */
bool determineDustExistence() { return dustSensorInterface(); }

/**
 * @brief The main controller of RVC.
 * @details Since we have decided that there is no branch to terminate the RVC
 * after turn it on, it infinitely loops
 */
void controller() {
  while (true) {
    bool *obstacleLocations;
    bool dustExsitence = false;
    bool freezeSensor = false;
    int tickCounter = 5;

    obstacleLocations = determineObstacleLocation();
    dustExistence = determineDustExistence();

    if (obstacleLocations[FRONT]) {
      tickCounter = 5;
      turnLeft();
    } else if (obstacleLocations[FRONT] && obstacleLocations[LEFT]) {
      tickCounter = 5;
      turnRight();
    } else if (obstacleLocations[FRONT] && obstacleLocations[LEFT] &&
               obstacleLocations[RIGHT]) {
      tickCounter = 5;
      moveBackward();
      turnLeft();
    } else if (dustExistence || tickCounter != 5) {
      powerUpAndMoveForward();
      if (--tickCounter == 0) {
        tickCounter = 5;
      }
    } else {
      moveForward();
    }
    free(obstacleLocations);
  }
}
