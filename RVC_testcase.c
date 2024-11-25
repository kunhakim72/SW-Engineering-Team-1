#include "RVC_software_engineering.h"

int testCount = 0;

void describe(char *description, int expected, int result) {
  ++testCount;
  if (expected == result) {
    printf("\033[1;32m[+] %d. Test for %s\033[0m\n", testCount, description);
    return;
  }
  printf("\033[1;31m[-] %d. Test for %s\033[0m\n", testCount, description);
  printf("\texpected: %d\n", expected);
  printf("\tresult: %d\n", result);
}

void testTurnLeft() {
  turnLeft();
  // 1. power option = off
  describe("call power off interface when turn left", POWER_OFF, power);
  // 2. motion = turn left
  describe("call turn left interface when turn left", true,
           callTurnLeftInterface);
  resetTestCondition();
}

void testTurnRight() {
  turnRight();
  // 1. power option = off
  describe("call power off interface when turn right", POWER_OFF, power);
  // 2. motion = turn right
  describe("call turn right interface when turn right", true,
           callTurnRightInterface);
  resetTestCondition();
}

void testMoveBackward() {
  moveBackward();
  // 1. power option = off
  describe("call power off interface when move backward", POWER_OFF, power);
  // 2. motion = move backward
  describe("call move backward interface when move backward", true,
           callMoveBackwardInterface);
  resetTestCondition();
}

void testMoveForward() {
  moveForward();
  // 1. power option = on
  describe("call power on interface when move forward", POWER_ON, power);
  // 2. motion = move forward
  describe("call move foward interface when move forward", true,
           callMoveForwardInterface);
  resetTestCondition();
}

void testPowerUpAndMoveFoward() {
  // 1. power option = up
  // 2. motion = move forward
}

void testDetermineObstacleLocation() {
  determineObstacleLocation();
  // 1. !L, !R, !F
  // 2. L, !R, !F
  // 3. !L, R, !F
  // 4. !L, !R, F
  // 5. L, R, !F
  // 6. L, !R, F
  // 7. !L, R, F
  // 8. L, F, R
}

void testDetermineDustExistence() {
  determineDustExistence();
  // 1. D
  // 2. !D
}

void testController() {
  // 1. F -> turnLeft
  // 2. F, L -> turnRight
  // 3. F, L, R -> moveBackward
  // 4. D -> powerUp
}

int main() {
  testMoveForward();
  testTurnLeft();
  testTurnRight();
  testMoveBackward();
  testPowerUpAndMoveFoward();
  testDetermineDustExistence();
  testDetermineObstacleLocation();
  testController();

  return 0;
}
