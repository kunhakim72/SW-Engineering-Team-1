#include "RVC_software_engineering.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// 스위트 초기화 및 정리 함수
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

// 테스트 케이스 함수

void testTurnLeftPowerOff(void) {
    turnLeft();
    CU_ASSERT_EQUAL(callPowerOffInterface, true);
    resetTestCondition();
}

void testTurnLeftInterface(void) {
    turnLeft();
    CU_ASSERT_EQUAL(callTurnLeftInterface, true);
    resetTestCondition();
}

void testTurnRightPowerOff(void) {
    turnRight();
    CU_ASSERT_EQUAL(callPowerOffInterface, true);
    resetTestCondition();
}

void testTurnRightInterface(void) {
    turnRight();
    CU_ASSERT_EQUAL(callTurnRightInterface, true);
    resetTestCondition();
}

void testMoveBackwardPowerOff(void) {
    moveBackward();
    CU_ASSERT_EQUAL(callPowerOffInterface, true);
    resetTestCondition();
}

void testMoveBackwardInterface(void) {
    moveBackward();
    CU_ASSERT_EQUAL(callMoveBackwardInterface, true);
    resetTestCondition();
}

void testMoveForwardPowerOn(void) {
    moveForward();
    CU_ASSERT_EQUAL(callPowerOnInterface, true);
    resetTestCondition();
}

void testMoveForwardInterface(void) {
    moveForward();
    CU_ASSERT_EQUAL(callMoveForwardInterface, true);
    resetTestCondition();
}

void testPowerUpAndMoveForwardPowerUp(void) {
    powerUpAndMoveForward();
    CU_ASSERT_EQUAL(callPowerUpInterface, true);
    resetTestCondition();
}

void testPowerUpAndMoveForwardInterface(void) {
    powerUpAndMoveForward();
    CU_ASSERT_EQUAL(callMoveForwardInterface, true);
    resetTestCondition();
}

void testMoveForward(void) {
  moveForward();
  CU_ASSERT_EQUAL(callPowerOnInterface, true);
  CU_ASSERT_EQUAL(callMoveForwardInterface, true);
  resetTestCondition();
}

void testPowerUpAndMoveForward(void) {
  powerUpAndMoveForward();
  CU_ASSERT_EQUAL(callPowerUpInterface, true);
  CU_ASSERT_EQUAL(callMoveForwardInterface, true);
  resetTestCondition();
}

void testDetermineObstacleLocation(void) {
  bool *obstacleLocations;

  setVenvObstaclesStatus(false, false, false);
  obstacleLocations = determineObstacleLocation();
  CU_ASSERT_EQUAL(obstacleLocations[FRONT], false);
  CU_ASSERT_EQUAL(obstacleLocations[LEFT], false);
  CU_ASSERT_EQUAL(obstacleLocations[RIGHT], false);
  resetTestCondition();
  free(obstacleLocations);

  setVenvObstaclesStatus(true, false, false);
  obstacleLocations = determineObstacleLocation();
  CU_ASSERT_EQUAL(obstacleLocations[FRONT], true);
  CU_ASSERT_EQUAL(obstacleLocations[LEFT], false);
  CU_ASSERT_EQUAL(obstacleLocations[RIGHT], false);
  resetTestCondition();
  free(obstacleLocations);
}

void testDetermineDustExistence(void) {
  setVenvFrontDustStatus(true);
  CU_ASSERT_EQUAL(determineDustExistence(), true);
  resetTestCondition();

  setVenvFrontDustStatus(false);
  CU_ASSERT_EQUAL(determineDustExistence(), false);
  resetTestCondition();
}

void testController(void) {
  setVenvObstaclesStatus(true, false, false);
  setVenvFrontDustStatus(false);
  controller();
  CU_ASSERT_EQUAL(callTurnLeft, true);
  resetTestCondition();

  setVenvObstaclesStatus(true, true, false);
  setVenvFrontDustStatus(false);
  controller();
  CU_ASSERT_EQUAL(callTurnRight, true);
  resetTestCondition();

  setVenvObstaclesStatus(true, true, true);
  setVenvFrontDustStatus(false);
  controller();
  CU_ASSERT_EQUAL(callMoveBackward, true);
  CU_ASSERT_EQUAL(callTurnLeft, true);
  resetTestCondition();

  setVenvObstaclesStatus(false, false, false);
  setVenvFrontDustStatus(true);
  controller();
  CU_ASSERT_EQUAL(callPowerUpAndMoveForward, true);
  resetTestCondition();

  setVenvObstaclesStatus(false, false, false);
  setVenvFrontDustStatus(false);
  controller();
  CU_ASSERT_EQUAL(callMoveForward, true);
  resetTestCondition();
}

int main() {
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  
    // Turn Left Suite
    CU_pSuite suiteTurnLeft = CU_add_suite("Suite_TurnLeft", init_suite, clean_suite);
    if (!suiteTurnLeft) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(suiteTurnLeft, "Test TurnLeft PowerOff", testTurnLeftPowerOff);
    CU_add_test(suiteTurnLeft, "Test TurnLeft Interface", testTurnLeftInterface);

    // Turn Right Suite
    CU_pSuite suiteTurnRight = CU_add_suite("Suite_TurnRight", init_suite, clean_suite);
    if (!suiteTurnRight) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(suiteTurnRight, "Test TurnRight PowerOff", testTurnRightPowerOff);
    CU_add_test(suiteTurnRight, "Test TurnRight Interface", testTurnRightInterface);

    // Move Backward Suite
    CU_pSuite suiteMoveBackward = CU_add_suite("Suite_MoveBackward", init_suite, clean_suite);
    if (!suiteMoveBackward) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(suiteMoveBackward, "Test MoveBackward PowerOff", testMoveBackwardPowerOff);
    CU_add_test(suiteMoveBackward, "Test MoveBackward Interface", testMoveBackwardInterface);


  CU_pSuite suiteMoveForward =
      CU_add_suite("Suite_MoveForward", init_suite, clean_suite);
  if (suiteMoveForward == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(suiteMoveForward, "test of moveForward", testMoveForward) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite suitePowerUpAndMoveForward =
      CU_add_suite("Suite_PowerUpAndMoveForward", init_suite, clean_suite);
  if (suitePowerUpAndMoveForward == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(suitePowerUpAndMoveForward, "test of powerUpAndMoveForward",
                  testPowerUpAndMoveForward) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite suiteDetermineObstacleLocation =
      CU_add_suite("Suite_DetermineObstacleLocation", init_suite, clean_suite);
  if (suiteDetermineObstacleLocation == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(suiteDetermineObstacleLocation,
                  "test of determineObstacleLocation",
                  testDetermineObstacleLocation) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite suiteDetermineDustExistence =
      CU_add_suite("Suite_DetermineDustExistence", init_suite, clean_suite);
  if (suiteDetermineDustExistence == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(suiteDetermineDustExistence, "test of determineDustExistence",
                  testDetermineDustExistence) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_pSuite suiteController =
      CU_add_suite("Suite_Controller", init_suite, clean_suite);
  if (suiteController == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (CU_add_test(suiteController, "test of controller", testController) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  // CU_automated_run_tests();
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}