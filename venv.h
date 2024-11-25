#include <stdio.h>
#include <stdbool.h>

bool venvFrontObstacle = false;
bool venvLeftObstacle = false;
bool venvRightObstacle = false;

bool venvFrontDust = false;

void setVenvObstaclesStatus(bool front, bool left, bool right){
  venvFrontObstacle = front;
  venvLeftObstacle = left;
  venvRightObstacle = right;
}

void setVenvFrontDustStatus(bool status) {
  venvFrontDust = status;
}