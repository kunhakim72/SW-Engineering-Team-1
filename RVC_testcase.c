#include "RVC_software_engineering.h"
#define TEST true

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
  describe("call power off interface when turn left", true,
           callPowerOffInterface);
  // 2. motion = turn left
  describe("call turn left interface when turn left", true,
           callTurnLeftInterface);
  resetTestCondition();
}

void testTurnRight() {
  turnRight();
  // 1. power option = off
  describe("call power off interface when turn right", true,
           callPowerOffInterface);
  // 2. motion = turn right
  describe("call turn right interface when turn right", true,
           callTurnRightInterface);
  resetTestCondition();
}

void testMoveBackward() {
  moveBackward();
  // 1. power option = off
  describe("call power off interface when move backward", true,
           callPowerOffInterface);
  // 2. motion = move backward
  describe("call move backward interface when move backward", true,
           callMoveBackwardInterface);
  resetTestCondition();
}

void testMoveForward() {
  moveForward();
  // 1. power option = on
  describe("call power on interface when move forward", true,
           callPowerOnInterface);
  // 2. motion = move forward
  describe("call move foward interface when move forward", true,
           callMoveForwardInterface);
  resetTestCondition();
}

void testPowerUpAndMoveFoward() {
  powerUpAndMoveForward();
  // 1. power option = up
  describe("call power up interface when power up and move forward", true,
           callPowerUpInterface);
  // 2. motion = move forward
  describe("call move foward interface when power up and move forward", true,
           callMoveForwardInterface);
  resetTestCondition();
}

void testDetermineObstacleLocation() {
  bool *obstacleLocations = (bool *)malloc(sizeof(bool) * 3);

  // 1. !F, !L, !R
  setVenvObstaclesStatus(false, false, false); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("front obstacle is false when sensor input is !F, !L, !R", false,
           obstacleLocations[FRONT]);
  describe("left obstacle is false when sensor input is !F, !L, !R", false,
           obstacleLocations[LEFT]);
  describe("right obstacle is false when sensor input is !F, !L, !R", false,
           obstacleLocations[RIGHT]);
  resetTestCondition();

  // 2. F, !L, !R
  setVenvObstaclesStatus(true, false, false); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("front obstacle is true when sensor input is F, !L, !R", true,
           obstacleLocations[FRONT]);
  describe("left obstacle is false when sensor input is F, !L, !R", false,
           obstacleLocations[LEFT]);
  describe("right obstacle is false when sensor input is F, !L, !R", false,
           obstacleLocations[RIGHT]);
  resetTestCondition();

  // 3. !F, L, !R
  setVenvObstaclesStatus(false, true, false); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("front obstacle is false when sensor input is !F, L, !R", false,
           obstacleLocations[FRONT]);
  describe("left obstacle is true when sensor input is !F, L, !R", true,
           obstacleLocations[LEFT]);
  describe("right obstacle is false when sensor input is !F, L, !R", false,
           obstacleLocations[RIGHT]);
  resetTestCondition();

  // 4. !F, !L, R
  setVenvObstaclesStatus(false, false, true); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("front obstacle is false when sensor input is !F, !L, R", false,
           obstacleLocations[FRONT]);
  describe("left obstacle is false when sensor input is !F, !L, R", false,
           obstacleLocations[LEFT]);
  describe("right obstacle is true when sensor input is !F, !L, R", true,
           obstacleLocations[RIGHT]);
  resetTestCondition();

  // 5. F, L, !R
  setVenvObstaclesStatus(true, true, false); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("call FRONT obstacle location on interface when determine obstacle "
           "location F, L, !R",
           venvFrontObstacle, obstacleLocations[FRONT]);
  describe("call LEFT obstacle location on interface when determine obstacle "
           "location F, L, !R",
           venvLeftObstacle, obstacleLocations[LEFT]);
  describe("call RIGHT obstacle location on interface when determine obstacle "
           "location F, L, !R",
           venvRightObstacle, obstacleLocations[RIGHT]);
  resetTestCondition();

  // 6. F, !L, R
  setVenvObstaclesStatus(true, false, true); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("call FRONT obstacle location on interface when determine obstacle "
           "location F, !L, R",
           venvFrontObstacle, obstacleLocations[FRONT]);
  describe("call LEFT obstacle location on interface when determine obstacle "
           "location F, !L, R",
           venvLeftObstacle, obstacleLocations[LEFT]);
  describe("call RIGHT obstacle location on interface when determine obstacle "
           "location F, !L, R",
           venvRightObstacle, obstacleLocations[RIGHT]);
  resetTestCondition();

  // 7. !F, L, R
  setVenvObstaclesStatus(false, true, true); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("call FRONT obstacle location on interface when determine obstacle "
           "location !F, L, R",
           venvFrontObstacle, obstacleLocations[FRONT]);
  describe("call LEFT obstacle location on interface when determine obstacle "
           "location !F, L, R",
           venvLeftObstacle, obstacleLocations[LEFT]);
  describe("call RIGHT obstacle location on interface when determine obstacle "
           "location !F, L, R",
           venvRightObstacle, obstacleLocations[RIGHT]);
  resetTestCondition();

  // 8. L, F, R
  setVenvObstaclesStatus(true, true, true); // front left right
  obstacleLocations = determineObstacleLocation();
  describe("call FRONT obstacle location on interface when determine obstacle "
           "location L, F, R",
           venvFrontObstacle, obstacleLocations[FRONT]);
  describe("call LEFT obstacle location on interface when determine obstacle "
           "location L, F, R",
           venvLeftObstacle, obstacleLocations[LEFT]);
  describe("call RIGHT obstacle location on interface when determine obstacle "
           "location L, F, R",
           venvRightObstacle, obstacleLocations[RIGHT]);
  resetTestCondition();

  free(obstacleLocations);
}

void testDetermineDustExistence() {
  // 1. D
  setVenvFrontDustStatus(true); // dust exists

  determineDustExistence();
  describe("detect dust when dust exists", true, determineDustExistence());

  resetTestCondition();

  // 2. !D
  setVenvFrontDustStatus(false); // dust doesn't exist

  determineDustExistence();
  describe("don't detect dust when dust doesn't exist", false,
           determineDustExistence());

  resetTestCondition();
}

void testController() {
  // 1. F -> turnLeft
  setVenvObstaclesStatus(true, false, false); // front left right
  setVenvFrontDustStatus(false);

  controller();
  describe("call turn left when obstacle is detected at front sensor", true,
           callTurnLeft); // power option = off
  resetTestCondition();

  // 2. F, L -> turnRight
  setVenvObstaclesStatus(true, true, false); // front left right
  setVenvFrontDustStatus(false);

  controller();
  describe(
      "call turn right when obstacles are detected at front and left sensor",
      true,
      callTurnRight); // power option = off
  resetTestCondition();

  // 3. F, L, R -> moveBackward
  setVenvObstaclesStatus(true, true, true); // front left right
  setVenvFrontDustStatus(false);

  controller();
  describe(
      "call move backward when obstacles are detected at front, left and right",
      true,
      callMoveBackward); // power option = off
  describe("call turn left when dust is detected at dust sensor", true,
           callTurnLeft); // power option = up
  resetTestCondition();

  // 4. D -> powerUp
  setVenvObstaclesStatus(false, false, false); // front left right
  setVenvFrontDustStatus(true);

  controller();
  describe(
      "call power up and move forward when dust is detected at dust sensor",
      true,
      callPowerUpAndMoveForward); // power option = up

  resetTestCondition();

  // 5. none of the sensor activated
  setVenvObstaclesStatus(false, false, false); // front left right
  setVenvFrontDustStatus(false);

  controller();
  describe("call move forward when none of the sensor is activated", true,
           callMoveForward); // power option = up

  resetTestCondition();
}

int main() {
  isTesting = true;

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
