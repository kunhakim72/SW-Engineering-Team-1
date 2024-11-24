#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef enum{
    POWER_UP_AND_MOVE_FORWARD,
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_LEFT,
    TURN_RIGHT,
} cleanerMotion;

typedef enum{
    POWER_UP = 5,
    ON,
    OFF,
} cleanerPowerOption;

// initialize obstacles location and dust existence
bool frontObstacle = false;
bool leftObstacle = false;
bool rightObstacle = false;

bool dustExistence = false;

// initialize motion and power option of RVC
cleanerMotion motion = MOVE_FORWARD;
cleanerPowerOption powerOption = ON;

// generates random number in range
int generateRandomNumberInRange(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void cleanerTurnLeft(){
    powerOption = OFF;
    motion = TURN_LEFT;
}

void cleanerTurnRight(){
    powerOption = OFF;
    motion = TURN_RIGHT;
}

void cleanerMoveBackward(){
    powerOption = OFF;
    motion = MOVE_BACKWARD;
}

void cleanerEnableMoveForward(){
    powerOption = ON;
    motion = MOVE_FORWARD;
}

// Each step of loop determines obstacles location
// 0 determines front, 1 determines left, 2 determines right, respectively.

void determineObstacleLocation(){
    int i;
    for(i = 0; i < 3; i++){
        int obstacleExists = generateRandomNumberInRange(0, 1);
        switch(i){
            case 0:
                if(obstacleExists) frontObstacle = true;
                else frontObstacle = false;
                break;
            case 1:
                if(obstacleExists) leftObstacle = true;
                else leftObstacle = false;
                break;
            case 2:
                if(obstacleExists) rightObstacle = true;
                else rightObstacle = false;
        }
    }
}

void determineDustExistence(){
    int dustExists = generateRandomNumberInRange(0, 1);
    if(dustExists) dustExistence = true;
    else dustExistence = false;
}

// A function that counts 5-ticks
// If a location of obstacles is fixed, it just loops 5 times and terminates
// Else, it determines a location of obstacles at every step of the loop
// then decide the next motion of RVC

void tickFiveSeconds(bool obstaclesAreFixed){
    int i;
    for(i = 0; i < 5; i++){
        if(obstaclesAreFixed){
            continue;
        }
        else{
            determineObstacleLocation();
            if(frontObstacle && leftObstacle && !rightObstacle){
                cleanerTurnRight();
                cleanerEnableMoveForward();
                return;
            }
            else if(frontObstacle && !leftObstacle && rightObstacle){
                cleanerTurnLeft();
                cleanerEnableMoveForward();
                return;
            }
            else if(frontObstacle && leftObstacle && rightObstacle){
                cleanerMoveBackward();
                cleanerTurnLeft();
                cleanerEnableMoveForward();
                return;
             }
         }
    }
}

// The main controller of RVC
// Since we have decided that there is no branch to terminate the RVC after turn it on,
// it infinitely loops

void controller(){
    while(true){
        determineObstacleLocation();
        //printf("%d %d %d\n", frontObstacle, leftObstacle, rightObstacle);
        if(frontObstacle && leftObstacle && !rightObstacle){
            cleanerTurnRight();
            // tick-5.. and obstacles location is fixed
            tickFiveSeconds(true);
            cleanerEnableMoveForward();
        }
        else if(frontObstacle && !leftObstacle && rightObstacle){
            cleanerTurnLeft();
            // tick-5.. and obstacles location is fixed
            tickFiveSeconds(true);
            cleanerEnableMoveForward();
        }
        else if(frontObstacle && leftObstacle && rightObstacle){
            cleanerMoveBackward();
            // tick-5 .. and obstacles location is fixed
            tickFiveSeconds(true);
            cleanerTurnLeft();
            // tick-5 .. and obstacles location is fixed
            tickFiveSeconds(true);
            cleanerEnableMoveForward();
        }
        // Here we assume that cleaner's motion is fixed to move forward
        determineDustExistence();
        if(dustExistence){
            powerOption = POWER_UP;
            // tick-5.. obstacles location is not fixed
            tickFiveSeconds(false);
            powerOption = ON;
        }
    }
}

int main() {
    srand(time(NULL));
    controller();
    return 0;
}