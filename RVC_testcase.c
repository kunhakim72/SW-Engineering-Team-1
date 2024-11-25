#include "RVC_software_engineering.h"

void testCleanerTurnLeft() {
  // 1. power option = off
  // 2. motion = turn left
}

void testCleanerTurnRight(){
  // 1. power option = off
  // 2. motion = turn right
}

void testCleanerMoveBackward(){
  // 1. power option = off
  // 2. motion = move backward
}

void testCleanerEnableMoveForward(){
  // 1. power option = on
  // 2. motion = move forward
}

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
  testCleanerEnableMoveForward();
  testCleanerTurnLeft();
  testCleanerTurnRight();
  testCleanerMoveBackward();
  testPowerUpAndMoveFoward();
  testDetermineDustExistence();
  testDetermineObstacleLocation();
  testController();
      
  return 0;
}


