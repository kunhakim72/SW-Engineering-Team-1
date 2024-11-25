#include "RVC_software_engineering.h"

void describe(char* name, int expected, int result) {
  if (expected ==  result) {
    printf("\033[1;32m[+] Test for %s success\033[0m\n", name);
    return;
  }
  printf("\033[1;31m[-] Test for %s failed\033[0m\n", name);
  printf("\texpected: %d\n", expected);
  printf("\tresult: %d\n", result);
}

void testTurnLeft() {
  turnLeft();
  // 1. power option = off
  describe("call power off interface when turn left", POWER_OFF, power);
  // 2. motion = turn left
  describe("call turn left interface when turn left", TURN_LEFT, motion);
}

void testTurnRight(){
  // 1. power option = off
  // 2. motion = turn right
}

void testMoveBackward(){
  // 1. power option = off
  // 2. motion = move backward
}

void testMoveForward(){
  // 1. power option = on
  // 2. motion = move forward
}

// ---- 준필

void testPowerUpAndMoveFoward() {
  // 1. power option = up
  // 2. motion = move forward
}

void testDetermineObstacleLocation() {
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



